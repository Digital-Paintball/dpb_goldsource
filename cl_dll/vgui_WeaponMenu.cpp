//=========== (C) Copyright 1996-2001 Valve, L.L.C. All rights reserved. ===========
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// Purpose: TFC Class Menu 
//
// $Workfile:     $
// $Date: 2004/01/04 23:54:08 $
//
//-----------------------------------------------------------------------------
// $Log: vgui_WeaponMenu.cpp,v $
// Revision 1.1  2004/01/04 23:54:08  jonah
// add client
//
//
// $NoKeywords: $
//=============================================================================

#include "VGUI_Font.h"
#include <VGUI_TextImage.h>

#include "hud.h"
#include "cl_util.h"
#include "camera.h"
#include "kbutton.h"
#include "cvardef.h"
#include "usercmd.h"
#include "const.h"
#include "camera.h"
#include "in_defs.h"
#include "parsemsg.h"

#include "vgui_int.h"
#include "vgui_TeamFortressViewport.h"
#include "vgui_ServerBrowser.h"

// Class Menu Dimensions
#define CLASSMENU_TITLE_X				XRES(40)
#define CLASSMENU_TITLE_Y				YRES(32)
#define CLASSMENU_TOPLEFT_BUTTON_X		XRES(40)
#define CLASSMENU_TOPLEFT_BUTTON_Y		YRES(80)
#define CLASSMENU_BUTTON_SIZE_X			XRES(124)
#define CLASSMENU_BUTTON_SIZE_Y			YRES(24)
#define CLASSMENU_BUTTON_SPACER_X		YRES(24)
#define CLASSMENU_BUTTON_SPACER_Y		YRES(8)
#define CLASSMENU_WINDOW_X				XRES(176)
#define CLASSMENU_WINDOW_Y				YRES(230)
#define CLASSMENU_WINDOW_SIZE_X			XRES(424)
#define CLASSMENU_WINDOW_SIZE_Y			YRES(162)
#define CLASSMENU_WINDOW_TEXT_X			XRES(150)
#define CLASSMENU_WINDOW_TEXT_Y			YRES(80)
#define CLASSMENU_WINDOW_NAME_X			XRES(150)
#define CLASSMENU_WINDOW_NAME_Y			YRES(8)
#define CLASSMENU_WINDOW_PLAYERS_Y		YRES(42)

// Creation
CWeaponMenuPanel::CWeaponMenuPanel(int iTrans, int iRemoveMe, int x,int y,int wide,int tall,int cat) : CMenuPanel(iTrans, iRemoveMe, x,y,wide,tall)
{
	// don't show class graphics at below 640x480 resolution
	bool bShowClassGraphic = true;
	if ( ScreenWidth < 640 )
	{
		bShowClassGraphic = false;
	}

	memset( m_pImages, 0, sizeof(m_pImages) );

	// Get the scheme used for the Titles
	CSchemeManager *pSchemes = gViewPort->GetSchemeManager();

	// schemes
	SchemeHandle_t hTitleScheme = pSchemes->getSchemeHandle( "Title Font" );
	SchemeHandle_t hClassWindowText = pSchemes->getSchemeHandle( "Briefing Text" );

	// color schemes
	int r, g, b, a;

	// Create the title


	// Create the Scroll panel
	m_pScrollPanel = new CTFScrollPanel( CLASSMENU_WINDOW_X, CLASSMENU_WINDOW_Y, CLASSMENU_WINDOW_SIZE_X, CLASSMENU_WINDOW_SIZE_Y );
	m_pScrollPanel->setParent(this);
	//force the scrollbars on, so after the validate clientClip will be smaller
	m_pScrollPanel->setScrollBarAutoVisible(false, false);
	m_pScrollPanel->setScrollBarVisible(true, true);
	m_pScrollPanel->setBorder( new LineBorder( Color(255 * 0.7,170 * 0.7,0,0) ) );
	m_pScrollPanel->validate();
	int clientWide=m_pScrollPanel->getClient()->getWide();

	//turn scrollpanel back into auto show scrollbar mode and validate
	m_pScrollPanel->setScrollBarAutoVisible(false,true);
	m_pScrollPanel->setScrollBarVisible(false,false);
	m_pScrollPanel->validate();




	
	
	ScrollPanel *pScrollPanel = new CTFScrollPanel( x + XRES(16),y + XRES(8)*2 + YRES(16), wide - XRES(32), tall - (YRES(48) + BUTTON_SIZE_Y*2) );
	pScrollPanel->setParent(this);
	
	//force the scrollbars on so clientClip will take them in account after the validate
	pScrollPanel->setScrollBarAutoVisible(false, false);
	pScrollPanel->setScrollBarVisible(true, true);
	pScrollPanel->validate();

	// Create the text panel
	TextPanel *pText = new TextPanel( "", 0,0, 64,64);
	pText->setParent( pScrollPanel->getClient() );

	// get the font and colors from the scheme
	pText->setFont( pSchemes->getFont(hClassWindowText) );
	pSchemes->getFgColor( hClassWindowText, r, g, b, a );
	pText->setFgColor( r, g, b, a );
	pSchemes->getBgColor( hClassWindowText, r, g, b, a );
	pText->setBgColor( r, g, b, a );
	pText->setText("BLEH BLEH\nBLEH BLEH\nBLEH BLEH\nBLEH BLEH\nBLEH BLEH\nLOL\nLOL\nLOL\nLOL\nLOL\nLOL\nLOL\nLOL\nLOL\n");

	// Get the total size of the MOTD text and resize the text panel
	int iScrollSizeX, iScrollSizeY;

	// First, set the size so that the client's wdith is correct at least because the
	//  width is critical for getting the "wrapped" size right.
	// You'll see a horizontal scroll bar if there is a single word that won't wrap in the
	//  specified width.
	pText->getTextImage()->setSize(pScrollPanel->getClientClip()->getWide(), pScrollPanel->getClientClip()->getTall());
	pText->getTextImage()->getTextSizeWrapped( iScrollSizeX, iScrollSizeY );
	
	// Now resize the textpanel to fit the scrolled size
	pText->setSize( iScrollSizeX , iScrollSizeY );

	//turn the scrollbars back into automode
	pScrollPanel->setScrollBarAutoVisible(true, true);
	pScrollPanel->setScrollBarVisible(false, false);

	pScrollPanel->validate();







	for (int i = 0; i <WPN_WEAPONS; i++)
	{
		char sz[256]; 
		if(!WPNnames[cat][i])
		{
			m_pButtons[i]=0;
			continue;
		}
		int iYPos = CLASSMENU_TOPLEFT_BUTTON_Y + ( (CLASSMENU_BUTTON_SIZE_Y + CLASSMENU_BUTTON_SPACER_Y) * i );
		
		// Class button
		m_pButtons[i] =new CommandButton( WPNnames[cat][i], CLASSMENU_TOPLEFT_BUTTON_X, iYPos, CLASSMENU_BUTTON_SIZE_X, CLASSMENU_BUTTON_SIZE_Y, false);
		m_pButtons[i]->setContentAlignment( vgui::Label::a_west );
		m_pButtons[i]->setParent( this );
		m_pButtons[i]->setVisible(true);
		m_pPanels[i] = new CTransparentPanel( 255, 0, 0, m_pScrollPanel->getClient()->getWide(), CLASSMENU_WINDOW_SIZE_Y );
		m_pPanels[i]->setParent( m_pScrollPanel->getClient() );
		
		// don't show class pic in lower resolutions
		int textOffs = XRES(8);

		if ( bShowClassGraphic )
		{
			textOffs = CLASSMENU_WINDOW_NAME_X;
		}

		// Create the Class Name Label
		Label *pNameLabel = new Label( WPNnames[cat][i], textOffs, CLASSMENU_WINDOW_NAME_Y );
		pNameLabel->setFont( pSchemes->getFont(hTitleScheme) ); 
		pNameLabel->setParent(m_pPanels[i]);
		pSchemes->getFgColor( hTitleScheme, r, g, b, a );
		pNameLabel->setFgColor( r, g, b, a );
		pSchemes->getBgColor( hTitleScheme, r, g, b, a );
		pNameLabel->setBgColor( r, g, b, a );
		pNameLabel->setContentAlignment( vgui::Label::a_west );

	/*	// Create the Class Image
		if ( bShowClassGraphic )
		{
			m_pImages[i] = new CImageLabel( WPNfnames[cat][i], 0, 0, CLASSMENU_WINDOW_TEXT_X, CLASSMENU_WINDOW_TEXT_Y );
			m_pImages[i]->setParent(this );
			m_pImages[i]->setVisible(false);
	//		pLabel->setVisible( false );
		}
*/
		// Create the Player count string
		// Open up the Class Briefing File
		sprintf(sz, "weapons/%s.txt", WPNfnames[cat][i]);
		char *cText = "Weapon Description not available.";
		char *pfile = (char *)gEngfuncs.COM_LoadFile( sz, 5, NULL );
		if (pfile)
		{
			cText = pfile;
			gEngfuncs.Con_Printf(pfile);
		}		// Create the Text info window
		TextPanel *pTextWindow = new TextPanel(cText, textOffs, CLASSMENU_WINDOW_TEXT_Y, (CLASSMENU_WINDOW_SIZE_X - textOffs)-5, CLASSMENU_WINDOW_SIZE_Y - CLASSMENU_WINDOW_TEXT_Y);
		pTextWindow->setParent( m_pPanels[i]);
		pTextWindow->setFont( pSchemes->getFont(hClassWindowText) );
		pSchemes->getFgColor( hClassWindowText, r, g, b, a );
		pTextWindow->setFgColor( r, g, b, a );
		pSchemes->getBgColor( hClassWindowText, r, g, b, a );
		pTextWindow->setBgColor( r, g, b, a );



		// Resize the Info panel to fit it all
		int wide,tall;
		pTextWindow->getTextImage()->getTextSizeWrapped( wide,tall);
		pTextWindow->setSize(wide,tall);

		int xx,yy;
		pTextWindow->getPos(xx,yy);
		int maxX=xx+wide;
		int maxY=yy+tall;

		//check to see if the image goes lower than the text
		//just use the red teams [0] images
		/*if(m_pClassImages[c][i]!=null)
		{
			m_pClassImages[0][i]->getPos(xx,yy);
			if((yy+m_pClassImages[0][i]->getTall())>maxY)
			{
				maxY=yy+m_pClassImages[0][i]->getTall();
			}
		}*/

		//m_pClassInfoPanel[i]->setBorder(new LineBorder());

	}

	m_iCurrentInfo = 0;

}


// Update
void CWeaponMenuPanel::Update()
{
/*	if (!g_iTeamNumber)
		return;*/
/*
	int	 iYPos = CLASSMENU_TOPLEFT_BUTTON_Y;

	// Cycle through the rest of the buttons
	for (int i = 0; i <= PC_RANDOM; i++)
	{
		bool bCivilian = (gViewPort->GetValidClasses(g_iTeamNumber) == -1);

		if ( bCivilian )
		{
			// If this team can only be civilians, only the civilian button's visible
			if (i == 0)
			{
				m_pButtons[0]->setVisible( true );
				SetActiveInfo( 0 );
				iYPos += CLASSMENU_BUTTON_SIZE_Y + CLASSMENU_BUTTON_SPACER_Y;
			}
			else
			{
				m_pButtons[i]->setVisible( false );
			}
		}
		else 
		{
			if ( m_pButtons[i]->IsNotValid() || i == 0 )
			{
				m_pButtons[i]->setVisible( false );
			}
			else
			{
				m_pButtons[i]->setVisible( true );
				m_pButtons[i]->setPos( CLASSMENU_TOPLEFT_BUTTON_X, iYPos );
				iYPos += CLASSMENU_BUTTON_SIZE_Y + CLASSMENU_BUTTON_SPACER_Y;

				// Start with the first option up
				if (!m_iCurrentInfo)
					SetActiveInfo( i );
			}
		}

		// Now count the number of teammembers of this class
		int iTotal = 0;
		for ( int j = 1; j < MAX_PLAYERS; j++ )
		{
			if ( g_PlayerInfoList[j].name == NULL )
				continue; // empty player slot, skip
			if ( g_PlayerExtraInfo[j].teamnumber == 0 )
				continue; // skip over players who are not in a team
			if ( g_PlayerInfoList[j].thisplayer )
				continue; // skip this player
			if ( g_PlayerExtraInfo[j].teamnumber != g_iTeamNumber )
				continue; // skip over players in other teams

			// If this team is forced to be civilians, just count the number of teammates
			if ( g_PlayerExtraInfo[j].playerclass != i && !bCivilian )
				continue;

			iTotal++;
		}

		char sz[256]; 
		sprintf(sz, m_sPlayersOnTeamString, iTotal);
		m_pPlayers[i]->setText( sz );

		// Set the text color to the teamcolor
		m_pPlayers[i]->setFgColor(	iTeamColors[g_iTeamNumber % iNumberOfTeamColors][0],
									iTeamColors[g_iTeamNumber % iNumberOfTeamColors][1],
									iTeamColors[g_iTeamNumber % iNumberOfTeamColors][2],
									0 );

		// set the graphic to be the team pick
		for ( int team = 0; team < MAX_TEAMS; team++ )
		{
			// unset all the other images
			if ( m_pClassImages[team][i] )
			{
				m_pClassImages[team][i]->setVisible( false );
			}

			// set the current team image
			if ( m_pClassImages[g_iTeamNumber-1][i] != NULL )
			{
				m_pClassImages[g_iTeamNumber-1][i]->setVisible( true );
			}
			else if ( m_pClassImages[0][i] )
			{
				m_pClassImages[0][i]->setVisible( true );
			}
		}
	}

	// If the player already has a class, make the cancel button visible
	if ( g_iPlayerClass )
	{
		m_pCancelButton->setPos( CLASSMENU_TOPLEFT_BUTTON_X, iYPos );
		m_pCancelButton->setVisible( true );
	}
	else
	{
		m_pCancelButton->setVisible( false );
	}*/
	gEngfuncs.Con_Printf("UPDATED!!\n");
}


//======================================
// Update the Class menu before opening it
void CWeaponMenuPanel::Open( void )
{
	Update();
	CMenuPanel::Open();
}

//-----------------------------------------------------------------------------
// Purpose: Called each time a new level is started.
//-----------------------------------------------------------------------------
void CWeaponMenuPanel::Initialize( void )
{
	setVisible( false );
	m_pScrollPanel->setScrollValue( 0, 0 );
}

//======================================
// Mouse is over a class button, bring up the class info
void CWeaponMenuPanel::SetActiveInfo( int iInput )
{
	// Remove all the Info panels and bring up the specified one
	for (int i = 0; i <= WPN_WEAPONS; i++)
	{
		if(!m_pButtons[i])
			break;
		m_pButtons[i]->setArmed( false );
	}
	m_pButtons[iInput]->setArmed( true );
	m_iCurrentInfo = iInput;

	m_pScrollPanel->setScrollValue(0,0);
	m_pScrollPanel->validate();
}


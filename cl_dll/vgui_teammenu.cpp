//=========== (C) Copyright 1996-2001 Valve, L.L.C. All rights reserved. ===========
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// Purpose: TFC Team Menu
//
// $Workfile:     $
// $Date: 2005/03/15 23:05:40 $
//
//-----------------------------------------------------------------------------
// $Log: vgui_teammenu.cpp,v $
// Revision 1.2  2005/03/15 23:05:40  jsherman
// buy menu
//
// Revision 1.1  2004/01/04 23:54:08  jonah
// add client
//
//
// $NoKeywords: $
//=============================================================================

#include "vgui_int.h"
#include "VGUI_Font.h"
#include "VGUI_ScrollPanel.h"
#include "VGUI_TextImage.h"

#include "hud.h"
#include "cl_util.h"
#include "vgui_TeamFortressViewport.h"

// Team Menu Dimensions
#define TEAMMENU_TITLE_X				XRES(40)
#define TEAMMENU_TITLE_Y				YRES(32)
#define TEAMMENU_TOPLEFT_BUTTON_X		XRES(40)
#define TEAMMENU_TOPLEFT_BUTTON_Y		YRES(80)
#define TEAMMENU_BUTTON_SIZE_X			XRES(124)
#define TEAMMENU_BUTTON_SIZE_Y			YRES(24)
#define TEAMMENU_BUTTON_SPACER_Y		YRES(8)
#define TEAMMENU_WINDOW_X				XRES(176)
#define TEAMMENU_WINDOW_Y				YRES(80)
#define TEAMMENU_WINDOW_SIZE_X			XRES(424)
#define TEAMMENU_WINDOW_SIZE_Y			YRES(312)
#define TEAMMENU_WINDOW_TITLE_X			XRES(16)
#define TEAMMENU_WINDOW_TITLE_Y			YRES(16)
#define TEAMMENU_WINDOW_TEXT_X			XRES(16)
#define TEAMMENU_WINDOW_TEXT_Y			YRES(48)
#define TEAMMENU_WINDOW_TEXT_SIZE_Y		YRES(178)
#define TEAMMENU_WINDOW_INFO_X			XRES(16)
#define TEAMMENU_WINDOW_INFO_Y			YRES(234)
      
// Creation
CTeamMenuPanel::CTeamMenuPanel(int iTrans, int iRemoveMe, int x,int y,int wide,int tall) : CMenuPanel(iTrans, iRemoveMe, x,y,wide,tall)
{
	// Get the scheme used for the Titles
	CSchemeManager *pSchemes = gViewPort->GetSchemeManager();

	// schemes
	SchemeHandle_t hTitleScheme = pSchemes->getSchemeHandle( "Title Font" );
	SchemeHandle_t hTeamWindowText = pSchemes->getSchemeHandle( "Briefing Text" );
	SchemeHandle_t hTeamInfoText = pSchemes->getSchemeHandle( "Team Info Text" );

	// get the Font used for the Titles
	Font *pTitleFont = pSchemes->getFont( hTitleScheme );
	int r, g, b, a;

	// Create the title
	Label *pLabel = new Label( "", TEAMMENU_TITLE_X, TEAMMENU_TITLE_Y );
	pLabel->setParent( this );
	pLabel->setFont( pTitleFont );
	pSchemes->getFgColor( hTitleScheme, r, g, b, a );
	pLabel->setFgColor( r, g, b, a );
	pSchemes->getBgColor( hTitleScheme, r, g, b, a );
	pLabel->setBgColor( r, g, b, a );
	pLabel->setContentAlignment( vgui::Label::a_west );
	pLabel->setText("Select Your Team");

	// Create the Info Window
	m_pTeamWindow  = new CTransparentPanel( 255, TEAMMENU_WINDOW_X, TEAMMENU_WINDOW_Y, TEAMMENU_WINDOW_SIZE_X, TEAMMENU_WINDOW_SIZE_Y );
	m_pTeamWindow->setParent( this );
	m_pTeamWindow->setBorder( new LineBorder( Color(255*0.7,170*0.7,0,0 )) );

	// Create the Map Name Label
	m_pMapTitle = new Label( "", TEAMMENU_WINDOW_TITLE_X, TEAMMENU_WINDOW_TITLE_Y );
	m_pMapTitle->setFont( pTitleFont ); 
	m_pMapTitle->setParent( m_pTeamWindow );
	pSchemes->getFgColor( hTitleScheme, r, g, b, a );
	m_pMapTitle->setFgColor( r, g, b, a );
	pSchemes->getBgColor( hTitleScheme, r, g, b, a );
	m_pMapTitle->setBgColor( r, g, b, a );
	m_pMapTitle->setContentAlignment( vgui::Label::a_west );

	// Create the Scroll panel
	m_pScrollPanel = new CTFScrollPanel( TEAMMENU_WINDOW_TEXT_X, TEAMMENU_WINDOW_TEXT_Y, TEAMMENU_WINDOW_SIZE_X - (TEAMMENU_WINDOW_TEXT_X * 2), TEAMMENU_WINDOW_TEXT_SIZE_Y );
	m_pScrollPanel->setParent(m_pTeamWindow);
	m_pScrollPanel->setScrollBarVisible(false, false);

	// Create the Map Briefing panel
	m_pBriefing = new TextPanel("", 0,0, TEAMMENU_WINDOW_SIZE_X - TEAMMENU_WINDOW_TEXT_X, TEAMMENU_WINDOW_TEXT_SIZE_Y );
	m_pBriefing->setParent( m_pScrollPanel->getClient() );
	m_pBriefing->setFont( pSchemes->getFont(hTeamWindowText) );
	pSchemes->getFgColor( hTeamWindowText, r, g, b, a );
	m_pBriefing->setFgColor( r, g, b, a );
	pSchemes->getBgColor( hTeamWindowText, r, g, b, a );
	m_pBriefing->setBgColor( r, g, b, a );

	m_pBriefing->setText( gHUD.m_TextMessage.BufferedLocaliseTextString("#Map_Description_not_available") );
	
	int iYPos = TEAMMENU_TOPLEFT_BUTTON_Y;

	m_pButtons[0] = new CommandButton( "Red Team", TEAMMENU_TOPLEFT_BUTTON_X, iYPos, TEAMMENU_BUTTON_SIZE_X, TEAMMENU_BUTTON_SIZE_Y, false);
	m_pButtons[0]->setParent( this );
	m_pButtons[0]->setContentAlignment( vgui::Label::a_west );
	m_pButtons[0]->setBoundKey('1');
	m_pButtons[0]->addActionSignal(new CMenuHandler_StringCommandWatch( "jointeam 1",1));
	m_pButtons[0]->setVisible( true );
	iYPos+= TEAMMENU_BUTTON_SIZE_Y + TEAMMENU_BUTTON_SPACER_Y;
	m_pButtons[1] = new CommandButton( "Blue Team", TEAMMENU_TOPLEFT_BUTTON_X, iYPos, TEAMMENU_BUTTON_SIZE_X, TEAMMENU_BUTTON_SIZE_Y, false);
	m_pButtons[1]->setParent( this );
	m_pButtons[1]->setContentAlignment( vgui::Label::a_west );
	m_pButtons[1]->setBoundKey('2');
	m_pButtons[1]->addActionSignal(new CMenuHandler_StringCommandWatch( "jointeam 2",1));
	m_pButtons[1]->setVisible( true );
	iYPos+= TEAMMENU_BUTTON_SIZE_Y + TEAMMENU_BUTTON_SPACER_Y;
	m_pButtons[2] = new CommandButton( "Auto-Assign", TEAMMENU_TOPLEFT_BUTTON_X, iYPos, TEAMMENU_BUTTON_SIZE_X, TEAMMENU_BUTTON_SIZE_Y, false);
	m_pButtons[2]->setParent( this );
	m_pButtons[2]->setContentAlignment( vgui::Label::a_west );
	m_pButtons[2]->addActionSignal(new CMenuHandler_StringCommandWatch( "jointeam 3",1));
	m_pButtons[2]->setBoundKey('3');
	m_pButtons[2]->setVisible( true );
	iYPos+= TEAMMENU_BUTTON_SIZE_Y + TEAMMENU_BUTTON_SPACER_Y;
	m_pButtons[3] = new CommandButton( "Spectator", TEAMMENU_TOPLEFT_BUTTON_X, iYPos, TEAMMENU_BUTTON_SIZE_X, TEAMMENU_BUTTON_SIZE_Y, false);
	m_pButtons[3]->setParent( this );
	m_pButtons[3]->setContentAlignment( vgui::Label::a_west );
	m_pButtons[3]->addActionSignal(new CMenuHandler_StringCommandWatch( "jointeam 0",1));
	m_pButtons[3]->setBoundKey('4');
	m_pButtons[3]->setVisible( true );
	iYPos+= TEAMMENU_BUTTON_SIZE_Y + TEAMMENU_BUTTON_SPACER_Y;

	m_pCancelButton = new CommandButton( "     CANCEL", TEAMMENU_TOPLEFT_BUTTON_X, iYPos, TEAMMENU_BUTTON_SIZE_X, TEAMMENU_BUTTON_SIZE_Y);
	m_pCancelButton->setParent( this );
	m_pCancelButton->addActionSignal( new CMenuHandler_TextWindow(HIDE_TEXTWINDOW) );

	// Create the Spectate button

	Initialize();
}

//-----------------------------------------------------------------------------
// Purpose: Called each time a new level is started.
//-----------------------------------------------------------------------------
void CTeamMenuPanel::Initialize( void )
{
	m_bUpdatedMapName = false;
	m_pScrollPanel->setScrollValue( 0, 0 );
}
//-----------------------------------------------------------------------------
// Purpose: Called everytime the Team Menu is displayed
//-----------------------------------------------------------------------------
void CTeamMenuPanel::Update( void )
{
	int	 iYPos = TEAMMENU_TOPLEFT_BUTTON_Y;


	if ( g_bPickedTeam )
		m_pCancelButton->setVisible( true );
	else
		m_pCancelButton->setVisible( false );
	// Set the Map Title
	if (!m_bUpdatedMapName)
	{
		const char *level = gEngfuncs.pfnGetLevelName();
		if (level && level[0])
		{
			char sz[256]; 
			char szTitle[256]; 
			char *ch;

			// Update the level name
			strcpy( sz, level );
			ch = strchr( sz, '/' );
			if (!ch)
				ch = strchr( sz, '\\' );
			strcpy( szTitle, ch+1 );
			ch = strchr( szTitle, '.' );
			*ch = '\0';
			m_pMapTitle->setText( szTitle );
			*ch = '.';

			// Update the map briefing
			strcpy( sz, level );
			ch = strchr( sz, '.' );
			*ch = '\0';
			strcat( sz, ".txt" );
			char *pfile = (char*)gEngfuncs.COM_LoadFile( sz, 5, NULL );
			if (pfile)
			{
				m_pBriefing->setText( pfile );

				// Get the total size of the Briefing text and resize the text panel
				int iXSize, iYSize;
				m_pBriefing->getTextImage()->getTextSize( iXSize, iYSize );
				m_pBriefing->setSize( iXSize, iYSize );
			}

			m_bUpdatedMapName = true;
		}
	}
	m_pButtons[0]->setArmed(false);
	m_pButtons[1]->setArmed(false);
	m_pButtons[2]->setArmed(false);
	m_pButtons[3]->setArmed(false);
	m_pCancelButton->setArmed(false);
	m_pScrollPanel->validate();
}

//=====================================
// Key inputs
bool CTeamMenuPanel::SlotInput( int iSlot )
{
	if(iSlot<1 || iSlot > 4)
		return false;
	if ( !m_pButtons[ iSlot ] )
		return false;
	if ( m_pButtons[ iSlot-1 ]->isVisible() )
	{
		m_pButtons[ iSlot-1 ]->fireActionSignal();
		return true;
	}

	return false;
}

//======================================
// Update the Team menu before opening it
void CTeamMenuPanel::Open( void )
{
	Update();
	CMenuPanel::Open();
}

void CTeamMenuPanel::paintBackground()
{
	// make sure we get the map briefing up
	if ( !m_bUpdatedMapName )
		Update();

	CMenuPanel::paintBackground();
}

//======================================
// Mouse is over a team button, bring up the class info
void CTeamMenuPanel::SetActiveInfo( int iInput )
{
	// Remove all the Info panels and bring up the specified one
/*	m_pSpectateButton->setArmed( false );
	for (int i = 1; i <= 5; i++)
	{
		m_pButtons[i]->setArmed( false );
		m_pTeamInfoPanel[i]->setVisible( false );
	}

	// 6 is Spectate
	if (iInput == 6)
	{
		m_pSpectateButton->setArmed( true );
	}
	else
	{
		m_pButtons[iInput]->setArmed( true );
		m_pTeamInfoPanel[iInput]->setVisible( true );
	}

	m_iCurrentInfo = iInput;

	m_pScrollPanel->validate();*/
}

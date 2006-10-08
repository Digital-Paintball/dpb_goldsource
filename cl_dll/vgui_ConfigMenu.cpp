#include"hud.h"
#include"cl_util.h"
#include"vgui_TeamFortressViewPort.h"//class definitions done here
#include"buy.h"
#include<VGUI_Font.h>
#include<VGUI_ScrollPanel.h>
#include<VGUI_TextImage.h>
#include"vgui_combobox.h"

#define ID_MARKER   0
#define ID_BARREL   1
#define ID_PAINT    2
#define ID_JERSEY   3
#define ID_MASK     4


#define PANEL_MODEL_X      XRES(40)
#define PANEL_MODEL_Y      YRES(40)
#define PANEL_MODEL_WIDE   XRES(270)
#define PANEL_MODEL_TALL   YRES(200)

#define PANEL_DESC_X       XRES(330)
#define PANEL_DESC_Y       PANEL_MODEL_Y
#define PANEL_DESC_WIDE    PANEL_MODEL_WIDE
#define PANEL_DESC_TALL    PANEL_MODEL_TALL

#define PANEL_SELECT_X     XRES(40)
#define PANEL_SELECT_Y     YRES(260)
#define PANEL_SELECT_WIDE  XRES(560)
#define PANEL_SELECT_TALL  YRES(180)
#define SELECTION_WIDE     XRES(90)
#define SELECTION_TALL     YRES(120)
#define SELECTION_Y				 YRES(290)
#define SELECT_MARKER      XRES(60)
#define SELECT_BARREL      XRES(165)
#define SELECT_PAINT       XRES(270)
#define SELECT_JERSEY      XRES(375)
#define SELECT_MASK        XRES(480)

#define HEADER_Y           YRES(10)
#define HEADER_WIDE        XRES(100)
#define HEADER_TALL        YRES(20)
#define HEADER_MARKER      XRES(30)
#define HEADER_BARREL      XRES(240)
#define HEADER_PAINT       XRES(450)

#define DONE_X             XRES(450)
#define DONE_Y             YRES(150)
#define DONE_WIDE          XRES(80)
#define DONE_TALL          YRES(20)

#define CREDITS_X          XRES(10)
#define CREDITS_Y          YRES(150)

#define PODS_X             XRES(10)
#define PODS_Y             YRES(120)
#define PODS_SPACE         XRES(5)
#define PODS_WIDE          XRES(15)
#define PODS_TALL          YRES(15)
char *color_names[PAINT_COLORS] = {
	" Yellow",
	" Green",
	" Purple",
	" Orange",
	" Grey",
	" Pink",
	" Blue"
};

char *jerseys[JERSEY_MAX] = {
	" Empire", 
  " Dye",
  " Proto",
	" JT"
};

char *masks[MASK_MAX] = {
  " Mask 1",
  " Mask 2",
  " Mask 3",
  " Mask 4"
};

char vgui_Model[255];

class CMenuHandler_BuyDone : public ActionSignal
{
public:
	void actionPerformed(Panel *panel)
	{
			gViewPort->m_pConfigMenu->SendConfig();
			gViewPort->HideTopMenu();
	}
};

class CMenuHandler_Pod : public ActionSignal
{
	int inc;
public:
	CMenuHandler_Pod(int i) { inc = i; }
	void actionPerformed(Panel *panel)
	{
		gViewPort->m_pConfigMenu->Pod(inc);
	}
};
//La simple.
typedef struct saveData_s
{
	int marker;
	int barrel;
	int pods;
	int paint;
	int jersey;
	int mask;
} saveData_t;

//tony; no output, if it can save, it'll save, if it can't, it doesn't.
void CConfigMenu::SaveSelection()
{
	char filename[512];
	FILE *file;
	saveData_t saveData;
	
	saveData.marker = m_Marker->m_iOption;
	saveData.barrel = m_Barrel->m_iOption;
	saveData.pods	= m_iPods;
	saveData.paint	= m_Paint->m_iOption;
	saveData.jersey = m_Jersey->m_iOption;
	saveData.mask	= m_Mask->m_iOption;

	_snprintf(filename, sizeof(filename), "%s/purchase.dat", gEngfuncs.pfnGetGameDirectory() );
	file = fopen(filename, "wb");
	if (file)
	{
		fwrite(&saveData, 1, sizeof(saveData), file);
		fclose(file);
	}
}
//Tony; no output, if it can load, it'll load, if it can't, it doesn't.
void CConfigMenu::LoadSelection()
{
//	char filename[512];
	byte *data = NULL;
	saveData_t *saveData = NULL;

//	_snprintf(filename, sizeof(filename), "%s/purchase.dat", gEngfuncs.pfnGetGameDirectory() );

	data = gEngfuncs.COM_LoadFile( "purchase.dat", 5, NULL );
//	gEngfuncs.Con_Printf("trying to load data..\n");
	imarker = -1; ibarrel = -1; ipods = 0; ipaint = -1; ijersey = -1; imask = -1;
	if (data != NULL)
	{
		saveData = (saveData_t*)data;
		
		imarker = saveData->marker;
		ibarrel = saveData->barrel;
		ipaint = saveData->paint;
		ijersey = saveData->jersey;
		imask = saveData->mask;
		ipods = saveData->pods;
		/*
		m_Marker->SelectItem(m_Marker->m_iOption = saveData->marker);		SetActiveInfo(ID_MARKER);
		m_Barrel->SelectItem(m_Barrel->m_iOption = saveData->barrel);		SetActiveInfo(ID_BARREL);
		m_Paint->SelectItem(m_Paint->m_iOption = saveData->paint);			SetActiveInfo(ID_PAINT);
		m_Jersey->SelectItem(m_Jersey->m_iOption = saveData->jersey);		SetActiveInfo(ID_JERSEY);
		m_Mask->SelectItem(m_Mask->m_iOption = saveData->mask);				SetActiveInfo(ID_MASK);
		m_iPods = saveData->pods;											SetActiveInfo(-1);
*/
//		gEngfuncs.Con_Printf("Loading Selection: %i %i %i %i %i\n", 
//			m_Marker->m_iOption, m_Barrel->m_iOption, m_iPods, m_Paint->m_iOption, m_Jersey->m_iOption,
//			m_Mask->m_iOption );
//		SetActiveInfo(-1); //test

		gEngfuncs.COM_FreeFile( data );
	}
}
void CConfigMenu::Reset()
{
	CMenuPanel::Reset();
}
void CConfigMenu::Pod(int inc)
{
	if(inc) {
		if(m_iPods<MAX_PODS) {
			int w=m_Marker->m_iOption!=-1?gWeapons[m_Marker->m_iOption].cost : 0;
			int b=m_Barrel->m_iOption!=-1?gBarrels[m_Barrel->m_iOption].cost : 0;
			int c=w+b+((m_iPods+1)*COST_POD);
			if(c<=m_iMaxCredits) {
				m_iPods++;
				SetActiveInfo(-1);
			}
		}
	} else if(m_iPods>0) {
		m_iPods--;
		SetActiveInfo(-1);
	}
}	
void CConfigMenu::setMaxCredits(int c)
{
	m_iMaxCredits=c;
	SetActiveInfo(-1);
}
void CConfigMenu::SetActiveInfo(int id)
{
	int x,y;
	char desc[512],*pfile;
	int mark=m_Marker->m_iOption;
	int w=mark!=-1?gWeapons[mark].cost : 0;
	int b=m_Barrel->m_iOption!=-1?gBarrels[m_Barrel->m_iOption].cost : 0;
	int c=w+b+(m_iPods*COST_POD);
	if(c>m_iMaxCredits) 
	{
		if(id==-1) 
		{
			mark=-1;
			m_Marker->reset(" Select Marker");
			m_Barrel->reset(" Select Barrel");
			m_iPods=0;
			strcpy(vgui_Model,"none");
			m_TextPanel->setText("\nSelect a marker from the list");
			m_TextPanel->getTextImage()->getTextSizeWrapped(x,y);
			m_TextPanel->setSize(x,y);

		} 
		else if(id==ID_MARKER) 
		{
			mark=-1;
			m_Marker->reset(" Too few credits");
			strcpy(vgui_Model,"none");
			m_TextPanel->setText("\n**Not enough credits for this item");
			m_TextPanel->getTextImage()->getTextSizeWrapped(x,y);
			m_TextPanel->setSize(x,y);
		} 
		else if(id==ID_BARREL) 
			m_Barrel->reset(" Too few credits");
	}	
	if ( id==ID_MARKER&&mark!=-1&&mark!=m_Last) 
	{
		sprintf(desc,"descriptions/%s.txt",gWeapons[mark].filename);
		sprintf(vgui_Model,"models/w_%s.mdl",gWeapons[mark].filename);
		pfile=(char*)gEngfuncs.COM_LoadFile(desc,5,NULL);
		if(pfile) 
		{
			m_TextPanel->setText(pfile);
			m_ScrollPanel->setScrollBarVisible(false,true);
			x=m_ScrollPanel->getClientClip()->getWide()-16;
			y=m_ScrollPanel->getClientClip()->getTall();
			m_TextPanel->setSize(x,y);
			m_TextPanel->getTextImage()->getTextSizeWrapped(x,y);
			m_TextPanel->setSize(x,y);
			m_ScrollPanel->setScrollBarAutoVisible(false,true);
			gEngfuncs.COM_FreeFile(pfile);
    }
		m_Last=mark;
		m_ScrollPanel->setScrollValue(0,0);
		m_ScrollPanel->validate();
	} 
	else if((id==ID_JERSEY||id==ID_MASK) && m_Jersey->m_iOption!=-1&&m_Mask->m_iOption!=-1)
 		 strcpy(vgui_Model,"models/smallplayer.mdl");

 	mark=m_Marker->m_iOption;
	w=mark!=-1?gWeapons[mark].cost : 0;
	b=m_Barrel->m_iOption!=-1?gBarrels[m_Barrel->m_iOption].cost : 0;
	c=w+b+m_iPods*COST_POD;
	sprintf(desc,"Credits: %i/%i",c,m_iMaxCredits);
	m_Credits->setText(desc);
	sprintf(desc,"Pods: %i",m_iPods);
	m_Pods->setText(desc);
	m_Done->setVisible(mark!=-1&&m_Barrel->m_iOption!=-1&&m_Paint->m_iOption!=-1
                     &&m_Jersey->m_iOption!=-1&&m_Mask->m_iOption!=-1);
}

void CConfigMenu::SendConfig()
{
	SaveSelection(); //Tony; save selection out.
	gEngfuncs.pfnClientCmd(UTIL_VarArgs("weaponconfig %i %i %i %i %i %i\n",
		m_Marker->m_iOption, m_Barrel->m_iOption, m_iPods,
		m_Paint->m_iOption,m_Jersey->m_iOption,m_Mask->m_iOption));
	m_Done->setArmed(false);
}
typedef struct {
	char *name;
	int x;
} HeaderLabel;
#define NUM_HEADERS 3
HeaderLabel Headers[NUM_HEADERS];
CConfigMenu::CConfigMenu(int iTrans,int iRemoveMe,int x,int y,int w,int t)
: CMenuPanel(0,iRemoveMe,x,y,w,t)
{

	LoadSelection(); //Tony; load the selection now.
	int i;
	char buf[255];
	CSchemeManager *pSchemes  = gViewPort->GetSchemeManager();
	SchemeHandle_t hBigText = pSchemes->getSchemeHandle( "Title Font" );
	SchemeHandle_t hSmallText = pSchemes->getSchemeHandle( "Briefing Text" );
	Font *pBigFont=pSchemes->getFont(hBigText);
	
	CTransparentPanel *pModel=new CTransparentPanel(0, PANEL_MODEL_X,
		PANEL_MODEL_Y, PANEL_MODEL_WIDE, PANEL_MODEL_TALL);
	pModel->setParent(this);
	pModel->setBorder(new LineBorder(Color(255*0.7,170*0.7,0,0)));
	
	CTransparentPanel *pDesc=new CTransparentPanel(iTrans, PANEL_DESC_X,
		PANEL_DESC_Y, PANEL_DESC_WIDE, PANEL_DESC_TALL);
	pDesc->setParent(this);
	pDesc->setBorder(new LineBorder(Color(255*0.7,170*0.7,0,0)));
	
	CTransparentPanel *pSelect=new CTransparentPanel(iTrans, PANEL_SELECT_X,
		PANEL_SELECT_Y, PANEL_SELECT_WIDE, PANEL_SELECT_TALL);
	pSelect->setParent(this);
	pSelect->setBorder(new LineBorder(Color(255*0.7,170*0.7,0,0)));

	if (imarker > -1 && imarker < WEAPON_MAX)
	{
		sprintf(buf," %s (%i)",gWeapons[imarker].name,gWeapons[imarker].cost);
		m_Marker=new ComboBox(SELECT_MARKER, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, WEAPON_MAX, buf,ID_MARKER,this);
	}
	else
	{
		m_Marker=new ComboBox(SELECT_MARKER, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, WEAPON_MAX, " Select Marker",ID_MARKER,this);
	}
	m_Marker->setParent(this);
	for(i=0;i<WEAPON_MAX;i++) {
		sprintf(buf," %s (%i)",gWeapons[i].name,gWeapons[i].cost);
		m_Marker->addItem(strdup(buf));
	}
	m_Marker->SelectItem(imarker);

	if (ibarrel > -1 && ibarrel < BARREL_MAX)
	{
		sprintf(buf," %s (%i)",gBarrels[ibarrel].name,gBarrels[ibarrel].cost);
		m_Barrel=new ComboBox(SELECT_BARREL, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, BARREL_MAX, buf,ID_BARREL,this);
	}
	else
	{
		m_Barrel=new ComboBox(SELECT_BARREL, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, BARREL_MAX, " Select Barrel",ID_BARREL,this);
	}
	m_Barrel->setParent(this);
	for(i=0;i<BARREL_MAX;i++) {
		sprintf(buf," %s (%i)",gBarrels[i].name,gBarrels[i].cost);
		m_Barrel->addItem(strdup(buf));
	}
	m_Barrel->SelectItem(ibarrel);

	if (ipaint > -1 && ipaint < PAINT_COLORS)
	{
		m_Paint=new ComboBox(SELECT_PAINT, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, PAINT_COLORS, color_names[ipaint],ID_PAINT,this);
	}
	else
	{
		m_Paint=new ComboBox(SELECT_PAINT, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, PAINT_COLORS, " Select Paint",ID_PAINT,this);
	}
	m_Paint->setParent(this);
	for(i=0;i<PAINT_COLORS;i++)
		m_Paint->addItem(color_names[i]);
	
	m_Paint->SelectItem(ipaint);

	if ( ijersey > -1 && ijersey < JERSEY_MAX)
	{
		m_Jersey=new ComboBox(SELECT_JERSEY, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, JERSEY_MAX, jerseys[ijersey],ID_JERSEY,this);
	}
	else
	{
		m_Jersey=new ComboBox(SELECT_JERSEY, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, JERSEY_MAX, " Select Jersey",ID_JERSEY,this);
	}
	m_Jersey->setParent(this);
	for(i=0;i<JERSEY_MAX;i++)
		m_Jersey->addItem(jerseys[i]);
	m_Jersey->SelectItem(ijersey);

	if (imask > -1 && imask < MASK_MAX)
	{
		m_Mask=new ComboBox(SELECT_MASK, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, MASK_MAX, masks[imask],ID_MASK,this);
	}
	else
	{
		m_Mask=new ComboBox(SELECT_MASK, SELECTION_Y, SELECTION_WIDE,
			SELECTION_TALL, MASK_MAX, " Select Mask",ID_MASK,this);
	}
	m_Mask->setParent(this);
	for(i=0;i<MASK_MAX;i++)
		m_Mask->addItem(masks[i]);
	m_Mask->SelectItem(imask);

	m_Done=new CommandButton("     Done",DONE_X,DONE_Y,DONE_WIDE,DONE_TALL);
	m_Done->setContentAlignment(vgui::Label::a_west);
	m_Done->setParent(pSelect);
	m_Done->setVisible(false);
	m_Done->addActionSignal(new CMenuHandler_BuyDone());

	m_ScrollPanel=new CTFScrollPanel(0,0,PANEL_DESC_WIDE,PANEL_DESC_TALL);
	m_ScrollPanel->setParent(pDesc);
	m_ScrollPanel->setBgColor(0,0,0,255);
	m_ScrollPanel->setScrollBarVisible(false,false);

	m_TextPanel=new TextPanel("",0,0,PANEL_DESC_WIDE,PANEL_DESC_TALL);
	m_TextPanel->setParent(m_ScrollPanel->getClient());
	m_TextPanel->setFont(pSchemes->getFont(hSmallText));
	m_TextPanel->setFgColor(Scheme::sc_primary1);
	m_TextPanel->setBgColor(0,0,0,255);
	m_TextPanel->setText("\nSelect a marker from the list");
	
	m_TextPanel->getTextImage()->getTextSizeWrapped(x,y);
	m_TextPanel->setSize(x,y);
	m_ScrollPanel->validate();
	
	m_Credits=new Label("",CREDITS_X,CREDITS_Y);
	m_Credits->setParent(pSelect);
	m_Credits->setBgColor(0,0,0,255);
	m_Credits->setFgColor(Scheme::sc_primary1);
	m_Credits->setFont(pBigFont);
	m_Credits->setContentAlignment(vgui::Label::a_west);
	m_Credits->setText("Credits:");
	
	m_Pods=new Label("",PODS_X,PODS_Y);
	m_Pods->setParent(pSelect);
	m_Pods->setBgColor(0,0,0,255);
	m_Pods->setFgColor(Scheme::sc_primary1);
	m_Pods->setFont(pBigFont);
	m_Pods->setContentAlignment(vgui::Label::a_west);
	m_Pods->setText("Pods: 0");
	
	x=m_Pods->getWide()+2*PODS_SPACE;
	y=PODS_Y+((m_Pods->getTall()-PODS_TALL)/2);
	CommandButton *pButton=new CommandButton("+",x,y,PODS_WIDE,PODS_TALL);
	pButton->setFont(pSchemes->getFont(hSmallText));
	pButton->setContentAlignment(vgui::Label::a_center);
	pButton->setParent(pSelect);
	pButton->addActionSignal(new CMenuHandler_Pod(1));
	pButton->setVisible(true);
	x+=PODS_SPACE+PODS_WIDE;
	pButton=new CommandButton("-",x,y, PODS_WIDE,PODS_TALL);
	pButton->setFont(pSchemes->getFont(hSmallText));
	pButton->setContentAlignment(vgui::Label::a_center);
	pButton->setParent(pSelect);
	pButton->addActionSignal(new CMenuHandler_Pod(0));
	pButton->setVisible(true);

	strcpy(vgui_Model,"none");

	m_Last=-1;
	m_iPods = 0;

	for (int i = 0; i < ipods; i++)
		Pod(1); //add a pod for each number of pods there are.

	m_iPods = ipods; //gruh?
}

#include "hud.h"
#include "cl_util.h"
#include "vgui_TeamFortressViewPort.h"//class definitions done here
#include "VGUI_Font.h"
#include "VGUI_ScrollPanel.h"
#include "VGUI_TextImage.h"
#include "vgui_combobox.h"

#define COMBO_BUTTON_TALL YRES(20)
#define COMBO_ITEM_TALL   YRES(15)
class IndexList 
{
private:
	void **data;
	int capacity;
	int size;
public:
	void *get(int i);
	void add(void *p);
	IndexList();
};

IndexList::IndexList()
{
	data=new void*[2];
	capacity=2;
	size=0;
}

void IndexList::add(void *p)
{
	if(size==capacity) {
		int i;
		capacity*=2;
		void **ndata=new void*[capacity];
		for(i=0;i<size;i++)
			ndata[i]=data[i];
		delete data;
		data=ndata;
	}
	data[size++]=p;
}
void* IndexList::get(int i)
{
	return data[i];
}
class ComboItem : public Button
{
public:
	virtual void paint();
	virtual void paintBackground();
	
	void cursorEntered();
	void cursorExited();
	ComboItem(char *s, int x,int y,int w,int h);
};

ComboItem::ComboItem(char *s, int x, int y, int w, int h)
 : Button(s,x,y,w,h)
{
	setFgColor(Scheme::sc_primary1);
//	setContentAlignment(vgui::Label:a_west);
}
void ComboItem::paint()
{
	if(isArmed())
		setFgColor(Scheme::sc_secondary2);
	else
		setFgColor(Scheme::sc_primary1);
	Button::paint();
}

void ComboItem::paintBackground()
{
	if(isArmed()) {
		drawSetColor(Scheme::sc_primary2);
		drawFilledRect(0,0,_size[0],_size[1]);
	}
}
class CHandler_ComboChoose: public CHandler_ButtonHighlight
{
private:
	ComboBox *m_Combo;
	int index;
public:
	CHandler_ComboChoose(Button *b,ComboBox *c,int i) 
	: CHandler_ButtonHighlight(b)
	{
		m_Combo=c;
		index=i;
	}
	virtual void cursorEntered(Panel *panel)
	{
		m_Combo->m_iSelected=index;
		CHandler_ButtonHighlight::cursorEntered(panel);
	}
};
class CHandler_CloseCombo : public ActionSignal
{
private:
	ComboBox *m_Combo;
	char *m_String;
public:
	CHandler_CloseCombo(ComboBox *c, char *s) 
	{ 
		m_Combo=c;
		m_String=s;
	}
	void actionPerformed(Panel *panel)
	{
		m_Combo->m_iOption=m_Combo->m_iSelected;
		m_Combo->m_Scroll->setVisible(false);
		m_Combo->m_Button->setText(m_String);
		m_Combo->m_Container->SetActiveInfo(m_Combo->m_iID);
		m_Combo->setSize(m_Combo->getWide(),m_Combo->m_Button->getTall());
	}
};
class CHandler_ShowCombo : public ActionSignal
{
private:
	ComboBox *m_Combo;
public:
	CHandler_ShowCombo(ComboBox *c) { m_Combo=c; }
	void actionPerformed(Panel *panel) 
	{
		m_Combo->setSize(m_Combo->getWide(),
			m_Combo->m_Button->getTall()+m_Combo->m_Scroll->getTall());
		m_Combo->m_Scroll->setVisible(true);
	}
};
ComboBox::ComboBox(int x,int y,int w,int h, int c,char *def,int id,
	CMenuPanel *cont) 
: Panel(x,y,w,h)
{
	
	CSchemeManager *pSchemes	= gViewPort->GetSchemeManager();
	SchemeHandle_t hSmallText	= pSchemes->getSchemeHandle( "Briefing Text" );
	
	setBgColor(0,0,0,255);
	m_Button=new CommandButton(def,0,0,w,COMBO_BUTTON_TALL);
	m_Button->setFont(pSchemes->getFont(hSmallText));
	m_Button->setTextAlignment(vgui::Label::a_west);
	m_Button->setParent(this);
	m_Button->addActionSignal(new CHandler_ShowCombo(this));

	m_Scroll=new CTFScrollPanel(0,COMBO_BUTTON_TALL,w,h-COMBO_BUTTON_TALL);
	m_Scroll->setParent(this);
	m_Scroll->setBgColor(0,0,0,255);
	m_Scroll->setScrollBarVisible(false,false);
	m_Scroll->setScrollBarAutoVisible(false,true);
	m_Scroll->validate();
	
	m_Options=new CTransparentPanel(100,0,0,w,
		m_Scroll->getTall());
	m_Options->setParent(m_Scroll->getClient());
	m_Options->setBorder(new LineBorder(Color(255*0.7,170*0.7,0,0)));

	setSize(getWide(),m_Button->getTall());
	m_iItems=0;
	m_iSelected=-1;	
	m_iOption=-1;
	m_iID=id;
	m_Container=cont;
	m_Scroll->setVisible(false);
}	
void ComboBox::addItem(char *s)
{
	CSchemeManager *pSchemes	= gViewPort->GetSchemeManager();
	SchemeHandle_t hSmallText	= pSchemes->getSchemeHandle( "Briefing Text" );
	int x,y;
	m_Scroll->setScrollBarVisible(false,true);
	x=getWide();//m_Scroll->getClientClip()->getWide()-16;
	ComboItem *b=new ComboItem(s,0,COMBO_ITEM_TALL*m_iItems,x,COMBO_ITEM_TALL);
	b->setParent(m_Options);
	b->setFont(pSchemes->getFont(hSmallText));
	b->setFgColor(Scheme::sc_primary1);
	b->setBgColor(0,0,0,255);
	b->setContentAlignment(vgui::Label::a_west);
	b->addInputSignal(new CHandler_ComboChoose(b,this,m_iItems));
	b->addActionSignal(new CHandler_CloseCombo(this,s));
	m_iItems++;
	
	m_Options->setSize(getWide(),COMBO_ITEM_TALL*m_iItems);
	m_Scroll->setScrollBarAutoVisible(false,true);
	m_Scroll->validate();
	
}
void ComboBox::reset(char *s)
{
	m_iSelected=-1;
	m_iOption=-1;
	m_Button->setText(s);
}


#ifndef VGUI_COMBOBOX_H
#define VGUI_COMBOBOX_H

class ComboBox: public Panel
{
private:
	int m_iID;
	CMenuPanel *m_Container;
	ScrollPanel *m_Scroll;
	CommandButton *m_Button;
	int m_iItems;
	CTransparentPanel *m_Options;
	int m_iSelected;
public:
	int m_iOption;
	ComboBox(int x,int y,int w,int h,int c,char *def,int id,CMenuPanel *cont);
	void addItem(char *s);
	void reset(char *s);
	friend class CHandler_ShowCombo;
	friend class CHandler_CloseCombo;
	friend class CHandler_ComboChoose;
};

#endif

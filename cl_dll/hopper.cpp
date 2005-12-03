#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "string.h"
#include "wrect.h"
#include"net_api.h"
#include"cweapon.h"
#include"vgui_teamfortressviewport.h"
extern CHud gHUD;

DECLARE_MESSAGE(m_Hopper, Hopper);
DECLARE_MESSAGE(m_Hopper, Tubes);
DECLARE_MESSAGE(m_Hopper, CurMarker);
DECLARE_MESSAGE(m_Hopper, Barrel);
int CHudHopper :: Init( void )
{
	HOOK_MESSAGE(Hopper);
	HOOK_MESSAGE(Tubes);
	HOOK_MESSAGE(CurMarker);
	HOOK_MESSAGE(Barrel);
	m_iHopper=m_iTube=m_iFullTubes=0;
	m_iCurWeapon=-1;
	m_iFlags |= HUD_ACTIVE;
	gHUD.AddHudElem( this );
	eHopper.top=106;
	eHopper.bottom=175;
	eHopper.left=33;
	eHopper.right=108;
	fHopper.top=8;
	fHopper.bottom=77;
	fHopper.left=33;
	fHopper.right=108;
	eTube.top=106;
	eTube.bottom=175;
	eTube.left=2;
	eTube.right=29;
	fTube.top=8;
	fTube.bottom=78;
	fTube.left=2;
	fTube.right=30;
	bg.top=98;
	bg.bottom=180;
	bg.left=0;
	bg.right=175;
	return 1;
}
int CHudHopper::VidInit( void )
{
	hopper=SPR_Load("sprites/newhud.spr");
	crosshair=SPR_Load("sprites/crosshair.spr");
	pb=SPR_Load("sprites/pb.spr");
	return 1;
}
int CHudHopper::MsgFunc_Hopper(const char *pszName,int iSize,void *pbuf) {
	BEGIN_READ(pbuf,iSize);
	m_iHopper=READ_BYTE();
	return 1;
}
int CHudHopper::MsgFunc_Tubes(const char *pszName,int iSize,void *pbuf) {
	BEGIN_READ(pbuf,iSize);
	m_iTube=READ_BYTE();
	m_iFullTubes=READ_BYTE();
	return 1;
}
int CHudHopper::MsgFunc_Barrel(const char *pszName,int iSize,void *pbuf) {
	BEGIN_READ(pbuf,iSize);
	m_iBarrel=READ_BYTE();
	return 1;
}
int CHudHopper::MsgFunc_CurMarker(const char *pszName,int iSize,void *pbuf) {
	BEGIN_READ(pbuf,iSize);
	m_iCurWeapon=READ_BYTE();
	if(m_iCurWeapon==0xff)
		m_iCurWeapon=-1;
	if(m_iCurWeapon!=-1&&weapons[m_iCurWeapon])
		weapons[m_iCurWeapon]->m_flIdle=weapons[m_iCurWeapon]->m_flPrimaryAttack=weapons[m_iCurWeapon]->m_flReload=weapons[m_iCurWeapon]->m_flSecondaryAttack=1.0f;
	return 1;
}

#define HOP_XPOS (32)
#define HOP_YPOS (7)

#define TUBE_XPOS (2)
#define TUBE_YPOS (7)

int CHudHopper::Draw(float flTime)
{
	int off;
	wrect_t area;
	if (( gHUD.m_iHideHUDDisplay & ( HIDEHUD_ALL )) || (gViewPort && !gViewPort->AllowedToPrintText())||g_iUser1)
		return 1;
	area.top=0;
	area.left=0;
	area.bottom=32;
	area.right=32;
	SPR_Set(crosshair,166,166,166);
	SPR_DrawAdditive(0,(ScreenWidth/2)-16,(ScreenHeight/2)-16,&area);

	SPR_Set(hopper,255,255,255);
	SPR_DrawHoles(0,0,-1,&bg);
	area=fHopper;
	off=((fHopper.bottom-fHopper.top)*(200-m_iHopper))/200;
	area.top+=off;
	if(area.top<area.bottom)
		SPR_DrawHoles(0,HOP_XPOS,HOP_YPOS+off,&area);
		
	area=fTube;
	off=((fTube.bottom-fTube.top)*(100-m_iTube))/100;
	area.top+=off;
	if(area.top<area.bottom)
		SPR_DrawHoles(0,TUBE_XPOS,TUBE_YPOS+off,&area);
	area.top=189;
	area.bottom=200;
	if(!m_iFullTubes && !m_iTube)
		area.left=0;
	else
		area.left=((m_iFullTubes+1)*10);
	area.right=area.left+11;
	SPR_DrawHoles(0,25,60,&area);
	FillRGBA(2,85,m_flStamina,5,233,0,0,200);
	return 1;
}

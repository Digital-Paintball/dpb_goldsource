#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "string.h"
#include "wrect.h"
#include "cl_entity.h"
#include"vgui_teamfortressviewport.h"
extern CHud gHUD;
DECLARE_MESSAGE(m_Flag,Flag);
int CHudFlag :: Init( void )
{
	HOOK_MESSAGE(Flag);
	gHUD.AddHudElem( this );
	area.top=0;
	area.bottom=32;
	area.left=0;
	area.right=43;
	return 1;
}
int CHudFlag :: VidInit( void )
{
	FLG=SPR_Load("sprites/flag.spr"); 
	return 1;
}
int CHudFlag::MsgFunc_Flag(const char *pszName,int iSize,void *pbuf)
{
	BEGIN_READ(pbuf,iSize);
	int idx=READ_BYTE();
	g_PlayerExtraInfo[idx].flag=READ_BYTE();
	gEngfuncs.Con_Printf("Got msg: %i\n",idx,g_PlayerExtraInfo[idx].flag);
	if(g_PlayerExtraInfo[gEngfuncs.GetLocalPlayer()->index].flag)
		m_iFlags|=HUD_ACTIVE;
	else 
		m_iFlags&=~HUD_ACTIVE;
	return 1;
}
extern float colors[3][3];
int CHudFlag::Draw(float flTime)
{
	if (( gHUD.m_iHideHUDDisplay & ( HIDEHUD_ALL )) || (gViewPort && !gViewPort->AllowedToPrintText()))
		return 1;

	SPR_Set(FLG,255,170,0);
	SPR_DrawHoles(0,122,26,&area);
	return 1;
}

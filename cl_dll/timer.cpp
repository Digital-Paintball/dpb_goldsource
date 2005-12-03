#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "string.h"
#include "wrect.h"
#include "cl_entity.h"
#include "event_api.h"
#include"vgui_teamfortressviewport.h"

extern vec3_t v_origin;
extern CHud gHUD;
DECLARE_MESSAGE(m_Timer,Timer);
int CHudTimer :: Init( void )
{
	HOOK_MESSAGE(Timer);
	m_iFlags |= HUD_ACTIVE;
	gHUD.AddHudElem( this );
	endtime=0;
	m_RoundState=0;
	return 1;
}
int CHudTimer :: VidInit( void )
{
	LCD=SPR_Load("sprites/newhud.spr");
	return 1;
}
int CHudTimer::MsgFunc_Timer(const char *pszName,int iSize,void *pbuf)
{
	BEGIN_READ(pbuf,iSize);
	m_RoundState=READ_BYTE();
	if(!m_RoundState)
		gHUD.m_Hopper.m_flStamina=100.0f;
	float time=(float)READ_SHORT();
	if(time==0.0f)
		m_iFlags&=~HUD_ACTIVE;
	else 
		m_iFlags|=HUD_ACTIVE;
	if(m_RoundState==1&&time!=0.0f)
	  gEngfuncs.pEventAPI->EV_PlaySound(0,v_origin,CHAN_STATIC,
				"weapons/start.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
	else if(m_RoundState==2)
	  gEngfuncs.pEventAPI->EV_PlaySound(0,v_origin,CHAN_STATIC,
				"weapons/end.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
	endtime=gHUD.m_flTime+time;
	return 1;
}
int CHudTimer::Draw(float flTime)
{
	if (g_iUser1||( gHUD.m_iHideHUDDisplay & ( HIDEHUD_ALL )) || (gViewPort && !gViewPort->AllowedToPrintText()))
		return 1;
	int s=(int)(endtime-flTime);
	if(s<10&&!m_RoundState)
		return 1;
	if(s<0)
		s=0;
	int m=s/60;
	s%=60;
	SPR_Set(LCD,255,255,255);
	if(m/10) 
		DrawLCDNumber(114,2,m/10);
	if(m)
		DrawLCDNumber(124,2,m%10);
	DrawLCDNumber(138,2,s/10);
	DrawLCDNumber(148,2,s%10);
	return 1;
}

void CHudTimer::DrawLCDNumber(int x,int y,int num)
{
	if(num>9||num<0)
		return;
	area.top=189;
	area.bottom=200;
	area.left=num*10;
	area.right=area.left+11;
	SPR_DrawHoles(0,x,y,&area);
}


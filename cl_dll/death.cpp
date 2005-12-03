#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "string.h"
#include "wrect.h"
#include"buy.h"
#include"vgui_teamfortressviewport.h"
#include "cweapon.h"
#define MAX_LINES 16


void CAM_ToThirdPerson(void);
void CAM_ToFirstPerson(void);
struct death {
	int killer;
	int victim;
	int weapon;
	char name[32];
};

death deaths[MAX_LINES];

extern float say_colors[16][3];

cvar_t *hud_elim_lines;

float *GetClientColor( int clientIndex )
{
	return say_colors[g_PlayerExtraInfo[clientIndex].teamnumber];    
}
static inline int num_lines() {
	if(hud_elim_lines->value<=2)
		return 2;
	if(hud_elim_lines->value>=MAX_LINES)
		return MAX_LINES;
	return (int)hud_elim_lines->value;
}
DECLARE_MESSAGE(m_Death,Death);
int CHudDeath::Init() {
	HOOK_MESSAGE(Death);
	hud_elim_lines=CVAR_CREATE("hud_elim_lines","3",FCVAR_ARCHIVE);
	gHUD.AddHudElem(this);
	m_iFlags |= HUD_ACTIVE;
	InitHUDData();
	return 1;
}
void CHudDeath::InitHUDData() 
{
	memset(deaths,0,sizeof(deaths));
	scroll_time=0.0f;
}
int CHudDeath::VidInit() {
	death=SPR_Load("sprites/death.spr");
	return 1;
}
int CHudDeath::MsgFunc_Death( const char *pszName, int iSize, void *pbuf ) {
	int i,j;
	int lines=num_lines();
	scroll_time=gHUD.m_flTime+5.0;
	for(i=0;i<lines;i++) 
		if((!deaths[i].victim)||(!g_PlayerInfoList[deaths[i].victim].name)) break;
	if(i==lines) {
		ScrollDeathUp(lines);
		i=lines-1;
	}
	BEGIN_READ(pbuf,iSize);
	deaths[i].killer=READ_BYTE();
	if(deaths[i].killer==0xff) deaths[i].killer=-1;
	deaths[i].victim=READ_BYTE();
	strncpy(deaths[i].name,READ_STRING(),31);
	if(deaths[i].victim<0||deaths[i].victim>gEngfuncs.GetMaxClients()||
		deaths[i].killer<-1||deaths[i].killer>gEngfuncs.GetMaxClients()) {
		deaths[i].victim=0;
		return 1;
	}
	for(j=0;j<WEAPON_MAX;j++) 
		if(!strcmp(deaths[i].name,gWeapons[j].name)) break;
	if(j!=WEAPON_MAX)
			deaths[i].weapon=j;
	else
			deaths[i].weapon=-1;
	g_PlayerExtraInfo[deaths[i].victim].dead = 1;
	if(deaths[i].victim==gEngfuncs.GetLocalPlayer()->index) {
		CAM_ToThirdPerson();
    if(gHUD.m_Hopper.m_iCurWeapon!=-1)
    	weapons[gHUD.m_Hopper.m_iCurWeapon]->Reset();
	}
	if(deaths[i].killer==-1)
		deaths[i].victim=0;
	gViewPort->UpdateOnPlayerInfo();
	return 1;
}
void CHudDeath::ScrollDeathUp(int lines) {
	if(deaths[0].victim&&g_PlayerInfoList[deaths[0].victim].name) {
		if(deaths[0].weapon>=0) {
			if(g_PlayerInfoList[deaths[0].killer].name)
				gEngfuncs.Con_Printf(" * %s marked %s with %s\n",g_PlayerInfoList[deaths[0].killer].name,g_PlayerInfoList[deaths[0].victim].name,deaths[0].name);
		} else if(deaths[0].killer==deaths[0].victim)
				gEngfuncs.Con_Printf(" * %s called himself out\n",g_PlayerInfoList[deaths[0].victim].name);
		else
			gEngfuncs.Con_Printf(" * %s was eliminated by %s\n",g_PlayerInfoList[deaths[0].victim].name,deaths[0].name);
	}
	memmove(deaths,deaths+1,sizeof(deaths[0])*(lines-1));
	memset(deaths+lines-1,0,sizeof(deaths[0]));
}

int CHudDeath::Draw(float flTime) {
	int y,vic,kil;
	wrect_t area;
	int lines=num_lines();
	for(int i=0;i<lines;i++) {
		if(g_PlayerInfoList[deaths[i].victim].name) {
			gEngfuncs.pfnDrawConsoleStringLen(g_PlayerInfoList[deaths[i].victim].name,&vic,&y);
			if(deaths[0].weapon>=0) {
				if(g_PlayerInfoList[deaths[0].killer].name) {
					gEngfuncs.pfnDrawConsoleStringLen(g_PlayerInfoList[deaths[i].victim].name,&vic,&y);
					gEngfuncs.pfnDrawConsoleStringLen(g_PlayerInfoList[deaths[i].killer].name,&kil,&y);
					y=g_PlayerExtraInfo[deaths[i].killer].teamnumber;
					gEngfuncs.pfnDrawSetTextColor(say_colors[y][0],say_colors[y][1],say_colors[y][2]);
					gEngfuncs.pfnDrawConsoleString(ScreenWidth-55-vic-kil,YRES(32)+5+i*20,g_PlayerInfoList[deaths[i].killer].name);
					y=g_PlayerExtraInfo[deaths[i].victim].teamnumber;
					gEngfuncs.pfnDrawSetTextColor(say_colors[y][0],say_colors[y][1],say_colors[y][2]);
					gEngfuncs.pfnDrawConsoleString(ScreenWidth-5-vic,YRES(32)+5+i*20,g_PlayerInfoList[deaths[i].victim].name);
					SPR_Set(death,255,255,255);			
					area.top=(deaths[i].weapon%12)*20;
					area.bottom=area.top+20;
					area.left=deaths[i].weapon>7?40:0;
					area.right=area.left+40;
					SPR_DrawHoles(0,ScreenWidth-vic-50,YRES(32)+5+i*20,&area);
				}
			} else {
				gEngfuncs.pfnDrawConsoleStringLen(g_PlayerInfoList[deaths[i].victim].name,&vic,&y);
				y=g_PlayerExtraInfo[deaths[i].victim].teamnumber;
				gEngfuncs.pfnDrawSetTextColor(say_colors[y][0],say_colors[y][1],say_colors[y][2]);
				gEngfuncs.pfnDrawConsoleString(ScreenWidth-5-vic,YRES(32)+5+i*20,g_PlayerInfoList[deaths[i].victim].name);
				SPR_Set(death,255,255,255);			
				area.top=140;
				area.bottom=160;
				area.left=40;
				area.right=80;
				SPR_DrawHoles(0,ScreenWidth-vic-50,YRES(32)+5+i*20,&area);
			}
		}
	}
	if(flTime>scroll_time) {
		ScrollDeathUp(lines);
		scroll_time=flTime+5.0f;
	}
	return 1;
}

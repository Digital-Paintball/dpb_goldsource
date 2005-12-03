#include"hud.h"
#include"cl_util.h"
#include"pm_defs.h"
#include"event_api.h"

extern float say_colors[16][3];
extern float curshot,lastshot;
cvar_t *cl_showbps;
int CHudName::Init() {
	gHUD.AddHudElem(this);
	cl_showbps=CVAR_CREATE("cl_showbps","0",FCVAR_ARCHIVE);
	m_iFlags |= HUD_ACTIVE;
	return 1;
}
int CHudName::VidInit() {
	return 1;
}
extern vec3_t v_origin,v_angles;
int CHudName::Draw(float flTime) {
	vec3_t v;
	int w,h,e,i;
	pmtrace_t tr;
	if(!g_iUser1) {
		AngleVectors(v_angles,v,NULL,NULL);
		VectorMA(v_origin,480.0f,v,v);
		gEngfuncs.pEventAPI->EV_PushPMStates();
		i=gEngfuncs.GetLocalPlayer()->index;
		gEngfuncs.pEventAPI->EV_SetSolidPlayers (  i - 1 );	
		gEngfuncs.pEventAPI->EV_PlayerTrace(v_origin,v,PM_NORMAL,-1,&tr);
		
		if(tr.fraction!=1.0f) {
			e=gEngfuncs.pEventAPI->EV_IndexFromTrace(&tr);
			if(e>=1&&e<=gEngfuncs.GetMaxClients()&&e!=i&&g_PlayerExtraInfo[e].teamnumber==g_iTeamNumber) {
				gEngfuncs.pfnDrawConsoleStringLen(g_PlayerInfoList[e].name,&w,&h);
				gEngfuncs.pfnDrawSetTextColor(say_colors[g_iTeamNumber][0],say_colors[g_iTeamNumber][1],say_colors[g_iTeamNumber][2]);
				gEngfuncs.pfnDrawConsoleString(XRES(320)-(w/2),YRES(240)+64,g_PlayerInfoList[e].name);
			}
		}
		gEngfuncs.pEventAPI->EV_PopPMStates();
		if(cl_showbps->value) {
			gEngfuncs.pfnDrawSetTextColor(1.0f,1.0f,1.0f);
			gEngfuncs.pfnDrawConsoleString(gHUD.m_scrinfo.iWidth-50,10,UTIL_VarArgs("%.1f bps",1.0f/(curshot-lastshot)));
		}
	}
	return 1;
}
#include  "extdll.h"
#include "wrect.h"
#include "cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include "cweapon.h"
#include "hud.h"
#include "cweapon.h"
#include "buy.h"
#include "vgui_TeamFortressViewport.h"
#include "vgui_combobox.h"
float curshot=0,lastshot=0;
void ClientWeapon::PrimaryAttack()
{
}
void ClientWeapon::SecondaryAttack()
{
}
void ClientWeapon::Idle()
{
}
void ClientWeapon::Reload()
{
}
void ClientWeapon::Reset()
{
	m_iReload=0;
	m_flReload=5.0f;
	m_flSecondaryAttack=5.0f;
	m_flPrimaryAttack=5.0f;
	m_flIdle=0.0f;
	m_bGunDown=0;
}
void ClientWeapon::DefReload(int aidle,int abegin)
{
	if(!m_iReload)
	{
		m_iReload=1;
		m_flReload=2.0f;
		m_flIdle=0.0f;
		m_flPrimaryAttack=2.0f;
		m_flSecondaryAttack=2.0f;
		m_bPrimaryAttack=0;
		m_bSecondaryAttack=0;
		SetAnim(aidle);
	}
	else if(m_iReload==1)
	{
		m_iReload=2;
		m_flReload=10.0f;
		SetAnim(abegin);
		gEngfuncs.pEventAPI->EV_PlaySound(gEngfuncs.GetLocalPlayer()->index, v_origin, CHAN_WEAPON, "weapons/reload.wav", gEngfuncs.pfnRandomFloat(0.92, 1.0), ATTN_NORM, 0, 98 + gEngfuncs.pfnRandomLong( 0, 3 ) );
	}
	else
	{
		m_flReload=10.0f;
	}
}
void ClientWeapon::Frame(double dt)
{
	if(g_Buttons & IN_DASH&&!m_bGunDown) {
		SetAnim(SEMI_HOLSTER);
		m_bGunDown=1;
	} else if(m_bGunDown && !(g_Buttons&IN_DASH)) {
		SetAnim(SEMI_DEPLOY);
		m_bGunDown=0;
		m_flReload=m_flPrimaryAttack=m_flSecondaryAttack=m_flIdle=1.0;
	}
	if((g_Buttons & IN_RELOAD) && m_flReload<=0 && gHUD.m_Hopper.m_iHopper<200 && gHUD.m_Hopper.m_iTube )
		Reload();
	else if(gHUD.m_Timer.m_RoundState&&(g_Buttons & IN_ATTACK ) && (!(g_Buttons&IN_RELOAD)) && m_flPrimaryAttack<=0  && m_bPrimaryAttack && gHUD.m_Hopper.m_iHopper>0)
		PrimaryAttack();
	else if(gHUD.m_Timer.m_RoundState&&(g_Buttons & IN_ATTACK2) && (!(g_Buttons&IN_RELOAD)) && m_flSecondaryAttack<=0 && m_bSecondaryAttack)
		SecondaryAttack();
	else if(m_flIdle<=0 && (!(g_Buttons&(IN_ATTACK |IN_ATTACK2))&& 
		((!(g_Buttons&IN_RELOAD)) || gHUD.m_Hopper.m_iHopper==200|| !gHUD.m_Hopper.m_iTube )))
		Idle();
	m_flPrimaryAttack-=dt;
	m_flSecondaryAttack-=dt;
	m_flIdle-=dt;
	m_flReload-=dt;
}
void ClientWeapon::IdleHandleReload(int arld,int aend)
{
	if(m_iReload==1)
	{
		SetAnim(aend);
		m_flReload=0;
		m_iReload=0;
	}
	else if(m_iReload==2)
	{
		SetAnim(arld);
		gEngfuncs.pEventAPI->EV_StopSound(gEngfuncs.GetLocalPlayer()->index,CHAN_WEAPON,"weapons/reload.wav");
		m_flReload=2.0f;
		m_flPrimaryAttack=2.0f;
		m_flSecondaryAttack=2.0f;
		m_iReload=1;
		m_flIdle=2.0f;
	}
}
void ClientWeapon::SetAnim(int anim)
{
	gEngfuncs.pfnWeaponAnim(anim,gHUD.m_Hopper.m_iBarrel);
}
extern int v_ground;
extern float v_height;
extern float v_speed;
void ClientWeapon::PaintballFire(float max)
{
	float punch;
	float f[3],r[3],u[3];
	gEngfuncs.pfnAngleVectors(v_angles,f,r,u);
	float sr,su;
	DPB_Seed(g_Random);
	lastshot=curshot;
	curshot=gEngfuncs.GetClientTime();
	punch=max*0.3;
	max*=gBarrels[gHUD.m_Hopper.m_iBarrel].scale;
	if(g_iUser4&U_PRONING) {
		max+=0.5*v_speed;
		punch*=0.1f;
	} else if(!gEngfuncs.pEventAPI->EV_LocalPlayerDucking()) {
		max+=5.0f+v_speed*0.25;
		punch*=0.2f;
	} else {
		max+=3.0f+v_speed*0.88;
		punch*=0.15f;
	}
	if(!v_ground) 
		max+=150.0f;

	//END CALC SHIT
	
	sr=DPB_RandomFloat(-max,max)/1000.0;
	su=DPB_RandomFloat(-max,max)/1000.0;
	vecmul(r,sr);
	vecmul(u,su);
	vecadd(f,r);
	vecadd(f,u);
	UTIL_Normalize(f);
	FirePaintball(v_origin,f,gEngfuncs.GetLocalPlayer()->index,gViewPort->m_pConfigMenu->m_Paint->m_iOption);
	CL_PunchAxes(punch);
}
void UTIL_Normalize(float *v)
{
	float len=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0]/=len;
	v[1]/=len;
	v[2]/=len;
}

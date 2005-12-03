#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CMag::PrimaryAttack()
{
	WPN_SOUND("weapons/mag.wav");
	PaintballFire(MAG_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/MAG_ROF;
	m_bPrimaryAttack=0;

}

void CMag::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CMag::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

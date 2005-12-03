#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CDM4::PrimaryAttack()
{
	WPN_SOUND("weapons/dm4.wav");
	PaintballFire(DM4_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/DM4_ROF;
	m_bPrimaryAttack=0;

}

void CDM4::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CDM4::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

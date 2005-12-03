#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CImpulse::PrimaryAttack()
{
	WPN_SOUND("weapons/impulse.wav");
	PaintballFire(IMPULSE_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/IMPULSE_ROF;
	m_bPrimaryAttack=0;

}

void CImpulse::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CImpulse::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

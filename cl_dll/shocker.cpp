#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CShocker::PrimaryAttack()
{
	PaintballFire(SHOCKER_ACC);
	WPN_SOUND("weapons/shocker.wav");
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/SHOCKER_ROF;
	m_bPrimaryAttack=0;

}

void CShocker::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CShocker::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

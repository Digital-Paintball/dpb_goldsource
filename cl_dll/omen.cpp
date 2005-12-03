#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void COmen::PrimaryAttack()
{
	WPN_SOUND("weapons/omen.wav");
	PaintballFire(OMEN_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/OMEN_ROF;
	m_bPrimaryAttack=0;

}

void COmen::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void COmen::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

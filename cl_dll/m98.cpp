#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CM98::PrimaryAttack()
{
	WPN_SOUND("weapons/m98.wav");
	PaintballFire(M98_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/M98_ROF;
	m_bPrimaryAttack=0;

}

void CM98::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CM98::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

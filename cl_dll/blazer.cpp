#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CBlazer::PrimaryAttack()
{
	WPN_SOUND("weapons/blazer.wav");
	PaintballFire(BLAZER_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/BLAZER_ROF;
	m_bPrimaryAttack=0;

}

void CBlazer::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CBlazer::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

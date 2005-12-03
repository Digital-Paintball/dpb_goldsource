#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"


void CEmag::PrimaryAttack()
{
	WPN_SOUND("weapons/emag.wav");
	PaintballFire(EMAG_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/EMAG_ROF;
	m_bPrimaryAttack=0;

}

void CEmag::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CEmag::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

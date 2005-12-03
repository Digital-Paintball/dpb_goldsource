#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CExcal::PrimaryAttack()
{
	WPN_SOUND("weapons/excal.wav");
	PaintballFire(EXCAL_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/EXCAL_ROF;
	m_bPrimaryAttack=0;

}

void CExcal::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CExcal::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

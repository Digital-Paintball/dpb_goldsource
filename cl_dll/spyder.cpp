#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CSpyder::PrimaryAttack()
{
	PaintballFire(SPYDER_ACC);
	SetAnim(SEMI_SHOOT);
	WPN_SOUND("weapons/spyder.wav");
	m_flPrimaryAttack=1/SPYDER_ROF;
	m_bPrimaryAttack=0;

}

void CSpyder::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CSpyder::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

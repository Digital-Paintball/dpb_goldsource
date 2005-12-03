#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CPhantom::PrimaryAttack()
{
	PaintballFire(PHANTOM_ACC);
	SetAnim(SEMI_SHOOT);
	WPN_SOUND("weapons/phantom.wav");
	m_bPrimaryAttack=0;
	m_bSecondaryAttack=1;
}

void CPhantom::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	if((!m_bSecondaryAttack)&&(!m_bPrimaryAttack)&&(!m_iReload)) {
		m_bPrimaryAttack=1;
		m_flPrimaryAttack=0.5/PHANTOM_ROF;
		SetAnim(PUMP_OUT);
	}
}

void CPhantom::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}
void CPhantom::SecondaryAttack()
{
	m_bSecondaryAttack=0;
	m_flIdle=0.5/PHANTOM_ROF;
	SetAnim(PUMP_IN);
}
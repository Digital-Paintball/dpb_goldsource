#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CSL68::PrimaryAttack()
{
	PaintballFire(SL68_ACC);
	SetAnim(SEMI_SHOOT);
	WPN_SOUND("weapons/sl68.wav");
	m_bPrimaryAttack=0;
	m_bSecondaryAttack=1;
}

void CSL68::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	if((!m_bSecondaryAttack)&&(!m_bPrimaryAttack)&&(!m_iReload)) {
		m_bPrimaryAttack=1;
		m_flPrimaryAttack=0.5/SL68_ROF;
		SetAnim(PUMP_OUT);
	}
}

void CSL68::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}
void CSL68::SecondaryAttack()
{
	m_bSecondaryAttack=0;
	m_flIdle=0.5/SL68_ROF;
	SetAnim(PUMP_IN);
}
#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CCocker::PrimaryAttack()
{
	PaintballFire(COCKER_ACC);
	SetAnim(COCKER_SHOOT1);
	WPN_SOUND("weapons/cocker1.wav");
	m_flIdle=0.5/COCKER_ROF;
	m_bPrimaryAttack=0;
}

void CCocker::Idle()
{	
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	if((!m_bPrimaryAttack)&&(!m_iReload)) {
		SetAnim(COCKER_SHOOT2);
		WPN_SOUND("weapons/cocker2.wav");
		m_bPrimaryAttack=1;
		m_flPrimaryAttack=0.5/COCKER_ROF;
	} 
}

void CCocker::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
#include"random.h"

void CMatrix::PrimaryAttack()
{
	WPN_SOUND("weapons/matrix.wav");
	PaintballFire(MATRIX_ACC);
	SetAnim(SEMI_SHOOT);
	m_flPrimaryAttack=1/MATRIX_ROF;
	m_bPrimaryAttack=0;

}

void CMatrix::Idle()
{
	IdleHandleReload(SEMI_RELOAD_END,SEMI_IDLE);
	m_bPrimaryAttack=1;
}

void CMatrix::Reload()
{	
	DefReload(SEMI_RELOAD_BEGIN,SEMI_RELOAD);
}

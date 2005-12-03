/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#include "extdll.h"
#include "util.h"
#include"player.h"

#include"pbgun.h"

LINK_ENTITY_TO_CLASS(weapon_sl68,CSL68);
void CSL68::Precache()
{
	PRECACHE_MODEL("models/w_sl68.mdl");
	PRECACHE_MODEL("models/p_sl68.mdl");
	PRECACHE_MODEL("models/v_sl68.mdl");
}
void CSL68::Spawn()
{
	Precache();
	m_iId=WEAPON_SL68;
	DefSpawn();

}


void CSL68::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_sl68.mdl","models/p_sl68.mdl",showanim);
}
void CSL68::Idle()
{
	IdleHandleReload();
	if((!m_bSecondaryAttack)&&(!m_bPrimaryAttack)&&(!m_iReload)) {
		m_bPrimaryAttack=1;
		m_flPrimaryAttack=0.5/SL68_ROF;
	}
}

void CSL68::PrimaryAttack()
{
	PaintballFire(SL68_ACC);
	m_bPrimaryAttack=0;
	m_bSecondaryAttack=1;
}

void CSL68::SecondaryAttack()
{
	m_bSecondaryAttack=0;
	m_flIdle=0.5/SL68_ROF;
}

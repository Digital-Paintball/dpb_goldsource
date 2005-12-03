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

LINK_ENTITY_TO_CLASS(weapon_cocker,CCocker);
void CCocker::Precache()
{
	PRECACHE_MODEL("models/p_cocker.mdl");
	PRECACHE_MODEL("models/v_cocker.mdl");
	PRECACHE_MODEL("models/w_cocker.mdl");
}
void CCocker::Spawn()
{
	Precache();
	m_iId=WEAPON_COCKER;
	DefSpawn();
	
}


void CCocker::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_cocker.mdl","models/p_cocker.mdl",showanim);
}
void CCocker::Idle()
{
	IdleHandleReload();
	if((!m_bPrimaryAttack)&&(!m_iReload)) {
		m_bPrimaryAttack=1;
		m_flPrimaryAttack=0.5/COCKER_ROF;
	}
}

void CCocker::PrimaryAttack()
{

	PaintballFire(COCKER_ACC);
	m_flIdle=0.5/COCKER_ROF;
	m_bPrimaryAttack=0;
}


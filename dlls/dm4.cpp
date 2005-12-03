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

LINK_ENTITY_TO_CLASS(weapon_dm4,CDM4);
void CDM4::Precache()
{
	PRECACHE_MODEL("models/p_dm4.mdl");
	PRECACHE_MODEL("models/v_dm4.mdl");
	PRECACHE_MODEL("models/w_dm4.mdl");
}
void CDM4::Spawn()
{
	Precache();
	m_iId=WEAPON_DM4;
	DefSpawn();
	
}


void CDM4::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_dm4.mdl","models/p_dm4.mdl",showanim);
}
void CDM4::Idle()
{
	IdleHandleReload();
	m_bPrimaryAttack=1;
}

void CDM4::PrimaryAttack()
{
	PaintballFire(DM4_ACC);
	m_flPrimaryAttack=1/DM4_ROF;
	m_bPrimaryAttack=0;
}


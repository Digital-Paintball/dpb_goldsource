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

LINK_ENTITY_TO_CLASS(weapon_omen,COmen);
void COmen::Precache()
{
	PRECACHE_MODEL("models/p_omen.mdl");
	PRECACHE_MODEL("models/v_omen.mdl");
	PRECACHE_MODEL("models/w_omen.mdl");
}
void COmen::Spawn()
{
	Precache();
	m_iId=WEAPON_OMEN;
	DefSpawn();
	
}


void COmen::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_omen.mdl","models/p_omen.mdl",showanim);
}
void COmen::Idle()
{
	IdleHandleReload();
	m_bPrimaryAttack=1;
}

void COmen::PrimaryAttack()
{
	PaintballFire(OMEN_ACC);
	m_flPrimaryAttack=1/OMEN_ROF;
	m_bPrimaryAttack=0;
}


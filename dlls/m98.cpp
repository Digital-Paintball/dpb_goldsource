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

LINK_ENTITY_TO_CLASS(weapon_m98,CM98);
void CM98::Precache()
{
	PRECACHE_MODEL("models/p_m98.mdl");
	PRECACHE_MODEL("models/v_m98.mdl");
	PRECACHE_MODEL("models/w_m98.mdl");
}
void CM98::Spawn()
{
	Precache();
	m_iId=WEAPON_M98;
	DefSpawn();
	
}


void CM98::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_m98.mdl","models/p_m98.mdl",showanim);
}
void CM98::Idle()
{
	IdleHandleReload();
	m_bPrimaryAttack=1;
}

void CM98::PrimaryAttack()
{
	PaintballFire(M98_ACC);
	m_flPrimaryAttack=1/M98_ROF;
	m_bPrimaryAttack=0;
}


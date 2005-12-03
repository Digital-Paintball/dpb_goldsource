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

LINK_ENTITY_TO_CLASS(weapon_a5,CA5);
void CA5::Precache()
{
	PRECACHE_MODEL("models/p_a5.mdl");
	PRECACHE_MODEL("models/v_a5.mdl");
	PRECACHE_MODEL("models/w_a5.mdl");
}
void CA5::Spawn()
{
	Precache();
	m_iId=WEAPON_A5;
	DefSpawn();
	
}


void CA5::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_a5.mdl","models/p_a5.mdl",showanim);
}
void CA5::Idle()
{
	IdleHandleReload();
	m_bPrimaryAttack=1;
}

void CA5::PrimaryAttack()
{
	PaintballFire(A5_ACC);
	m_flPrimaryAttack=1/A5_ROF;
	m_bPrimaryAttack=0;
}


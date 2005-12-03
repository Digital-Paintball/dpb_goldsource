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
// testing
LINK_ENTITY_TO_CLASS(weapon_bush,CBush);
void CBush::Precache()
{
	PRECACHE_MODEL("models/p_bush.mdl");
	PRECACHE_MODEL("models/v_bush.mdl");
	PRECACHE_MODEL("models/w_bush.mdl");
}
void CBush::Spawn()
{
	Precache();
	m_iId=WEAPON_BUSH;
	DefSpawn();
	
}


void CBush::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_bush.mdl","models/p_bush.mdl",showanim);
}
void CBush::Idle()
{
	IdleHandleReload();
	m_bPrimaryAttack=1;
}

void CBush::PrimaryAttack()
{

	PaintballFire(BUSH_ACC);
	m_flPrimaryAttack=1/BUSH_ROF;
	m_bPrimaryAttack=0;
}


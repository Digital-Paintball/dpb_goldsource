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

LINK_ENTITY_TO_CLASS(weapon_mag,CMag);
void CMag::Precache()
{
	PRECACHE_MODEL("models/p_mag.mdl");
	PRECACHE_MODEL("models/v_mag.mdl");
	PRECACHE_MODEL("models/w_mag.mdl");
}
void CMag::Spawn()
{
	Precache();
	m_iId=WEAPON_MAG;
	DefSpawn();
	
}


void CMag::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_mag.mdl","models/p_mag.mdl",showanim);
}
void CMag::Idle()
{
	IdleHandleReload();
	m_bPrimaryAttack=1;
}

void CMag::PrimaryAttack()
{

	PaintballFire(MAG_ACC);
	m_flPrimaryAttack=1/MAG_ROF;
	m_bPrimaryAttack=0;
}


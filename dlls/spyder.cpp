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

LINK_ENTITY_TO_CLASS(weapon_spyder,CSpyder);
void CSpyder::Precache()
{
	PRECACHE_MODEL("models/p_spyder.mdl");
	PRECACHE_MODEL("models/v_spyder.mdl");
	PRECACHE_MODEL("models/w_spyder.mdl");
}
void CSpyder::Spawn()
{
	Precache();
	m_iId=WEAPON_SPYDER;
	DefSpawn();
	
}


void CSpyder::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_spyder.mdl","models/p_spyder.mdl",showanim);
}
void CSpyder::Idle()
{
	IdleHandleReload();
	m_bPrimaryAttack=1;
}

void CSpyder::PrimaryAttack()
{

	PaintballFire(SPYDER_ACC);
	m_flPrimaryAttack=1/SPYDER_ROF;
	m_bPrimaryAttack=0;
}


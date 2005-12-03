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

LINK_ENTITY_TO_CLASS(weapon_phantom,CPhantom);
void CPhantom::Precache()
{
	PRECACHE_MODEL("models/w_phantom.mdl");
	PRECACHE_MODEL("models/p_phantom.mdl");
	PRECACHE_MODEL("models/v_phantom.mdl");
}
void CPhantom::Spawn()
{
	Precache();
	m_iId=WEAPON_PHANTOM;
	DefSpawn();

}


void CPhantom::Deploy(int showanim)
{
	DefDeploy(SEMI_DEPLOY,"models/v_phantom.mdl","models/p_phantom.mdl",showanim);
}
void CPhantom::Idle()
{
	IdleHandleReload();
	if((!m_bSecondaryAttack)&&(!m_bPrimaryAttack)&&(!m_iReload)) {
		m_bPrimaryAttack=1;
		m_flPrimaryAttack=0.5/PHANTOM_ROF;
	}
}

void CPhantom::PrimaryAttack()
{
	PaintballFire(PHANTOM_ACC);
	m_bPrimaryAttack=0;
	m_bSecondaryAttack=1;
}

void CPhantom::SecondaryAttack()
{
	m_bSecondaryAttack=0;
	m_flIdle=0.5/PHANTOM_ROF;
}

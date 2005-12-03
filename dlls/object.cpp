#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "soundent.h"
#include "animation.h"
#include "object.h"
#include "rules.h"
#include "game.h"
extern int gmsgFlag;
void CObject::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev),"models/flag.mdl");
	pev->movetype=MOVETYPE_TOSS;
	pev->solid=SOLID_TRIGGER;
	pev->sequence=1;
	pev->skin=pev->team;
	pev->owner=NULL;
	pev->takedamage=DAMAGE_NO;
	SetThink(NULL);
	SetTouch(&CObject::Touch);
	Moved=0;
	m_Owner=0;
  pev->framerate=1.0;
  pev->frame=0;
	pev->nextthink=gpGlobals->time+10;
}
void CObject::Precache()
{
	PRECACHE_MODEL("models/flag.mdl");
}
void CObject::Touch(CBaseEntity *pOther)
{
	if(!pOther->IsPlayer())
		return;
	CBasePlayer* pPlayer=(CBasePlayer*)pOther;
	if(!pPlayer->pev->solid)
		return;
	if(mp_returnflag.value&&Moved&&pev->team==pPlayer->pev->team)
	{
		m_Owner->Flag(pev->team);
		return;
	}
	if(pPlayer->pev->solid==SOLID_NOT||pPlayer->m_Object||gpGlobals->time<pPlayer->m_flPickupTime)
		return;
	if(pev->team&&pev->team==pPlayer->pev->team)
		return;
	SetTouch(NULL);
	SetThink(NULL);
	pPlayer->m_Object=this;
	pev->owner=pPlayer->edict();
	pev->solid=SOLID_NOT;
	pev->effects|=EF_NODRAW;
	pev->movetype=MOVETYPE_FOLLOW;
	pev->aiment=pPlayer->edict();
	MESSAGE_BEGIN(MSG_ALL,gmsgFlag,NULL);
		WRITE_BYTE(pPlayer->entindex());
		WRITE_BYTE(1);
	MESSAGE_END();
	Moved=1;
	pev->nextthink=-1;
}
LINK_ENTITY_TO_CLASS(cflag,CObject);
void CObjectSpawner::Spawn()
{
	gRules.m_CFlag=this;
	pev->team=0;
	pev->movetype=MOVETYPE_NONE;
	pev->solid=SOLID_NOT;
	SetThink(NULL);
	SetTouch(NULL);
	pev->effects|=EF_NODRAW;
	m_pFlag=0;
	Flag(FLAG_CENTER);
	pev->nextthink=-1;
}
void CRed::Spawn()
{
	pev->team=1;
	gRules.m_RFlag=this;
	pev->movetype=MOVETYPE_NONE;
	pev->solid=SOLID_NOT;
	SetThink(NULL);
	SetTouch(NULL);
	pev->effects|=EF_NODRAW;
	m_pFlag=0;
	Flag(FLAG_RED);
	pev->nextthink=-1;
}
void CBlue::Spawn()
{
	pev->team=2;
	gRules.m_BFlag=this;
	pev->movetype=MOVETYPE_NONE;
	pev->solid=SOLID_NOT;
	SetThink(NULL);
	SetTouch(NULL);
	pev->effects|=EF_NODRAW;
	m_pFlag=0;
	Flag(FLAG_BLUE);
	pev->nextthink=-1;
}
void CObjectSpawner::Flag(int team)
{
	CObject *obj=0;
	obj=(CObject*)CBaseEntity::Create("cflag",pev->origin,pev->angles,NULL);
	if(obj)
	{
		obj->pev->team=obj->pev->skin=team;
		obj->m_Owner=this;
	}
	if(m_pFlag)
		UTIL_Remove(m_pFlag);
	m_pFlag=obj;
}
void CCapPoint::Spawn()
{
	pev->movetype=MOVETYPE_NONE;
	pev->solid=SOLID_TRIGGER;
	SetThink(NULL);
	SetTouch(&CCapPoint::Touch);
	pev->effects|=EF_NODRAW;
	SET_MODEL(edict(), STRING(pev->model));
	pev->nextthink=gpGlobals->time+11;
}
extern int gmsgScoreInfo;
void CCapPoint::Touch(CBaseEntity *pOther)
{
	if(!pOther->IsPlayer())
		return;
	CBasePlayer* pPlayer=(CBasePlayer*)pOther;
	if(gRules.m_RoundState!=ROUND_ACTIVE||!pPlayer->m_Object||pev->team!=pPlayer->pev->team)
			return;
	pPlayer->pev->frags++;
	for(int i=1;i<=gpGlobals->maxClients;i++)
	{
		CBasePlayer *p=(CBasePlayer*)UTIL_PlayerByIndex(i);
		if(!p)
			continue;
		if(p->pev->team==pPlayer->pev->team) {
			p->pev->frags++;
			MESSAGE_BEGIN( MSG_ALL, gmsgScoreInfo );
				WRITE_BYTE(i);
				WRITE_SHORT(p->pev->frags );
				WRITE_SHORT(p->m_iDeaths );
				WRITE_SHORT( 0 );
				WRITE_SHORT(p->pev->team);
			MESSAGE_END();
		}
	}
	if(pPlayer->pev->team==TEAM_RED)
		gRules.EndRound(WIN_RED);
	else
		gRules.EndRound(WIN_BLUE);
	
	pev->nextthink=-1;
}
LINK_ENTITY_TO_CLASS(item_flag_center,CObjectSpawner);
LINK_ENTITY_TO_CLASS(item_flag_red,CRed);
LINK_ENTITY_TO_CLASS(item_flag_blue,CBlue);
LINK_ENTITY_TO_CLASS(func_goalpoint,CCapPoint);

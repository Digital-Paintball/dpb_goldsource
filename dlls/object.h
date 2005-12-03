#ifndef OBJECT_H
#define OBJECT_H
#define FLAG_CENTER 0
#define FLAG_RED	1
#define FLAG_BLUE	2
#include "animation.h"
class CObjectSpawner;

class CObject: public CBaseAnimating
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void EXPORT Touch(CBaseEntity *pOther);
	BOOL Moved;
	CObjectSpawner *m_Owner;
};
class CObjectSpawner:public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Flag(int i);
	CObject* m_pFlag;
};
class CRed:public CObjectSpawner
{
public:
	virtual void Spawn();
};
class CBlue:public CObjectSpawner
{
public:
	virtual void Spawn();
};
class CCapPoint: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void EXPORT Touch(CBaseEntity *pOther);
};
#endif 

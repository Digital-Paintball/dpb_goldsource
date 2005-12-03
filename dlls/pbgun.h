#ifndef PBGUN_H
#define PBGUN_H


#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include"buy.h"
class CPaintballGun : public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Deploy(int showanim);
	virtual void Holster();
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Idle();
	virtual void Reload();
	void Touch(CBaseEntity *pOther);
	void WeaponPostThink();
	void GiveToPlayer(CBasePlayer *pPlayer);
	void DefDeploy(int seq,char *v_model,char* p_model,int showanim);
	void PaintballFire(float max);
	void DefSpawn();
	void IdleHandleReload();
	float m_flIdle;
	float m_flPrimaryAttack;
	float m_flSecondaryAttack;
	float m_flReload;

	int m_iId;
	int m_iReload;
	int m_bPrimaryAttack;
	int m_bSecondaryAttack;
	int m_iHopper;
	CBasePlayer *player;
};

class CAngel: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class CEmag: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};
class CShocker: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};
class CM98: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class CA5: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class CBlazer: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class COmen: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class CDM4: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};
class CBush: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class CTimmy: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};
class CCocker: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};
class COrracle: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class CSpyder: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class CMag: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};
class CExcal: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};
class CMatrix: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};

class CImpulse: public CPaintballGun
{
public:
	 void Spawn();
	 void Precache();
	 void Deploy(int showanim);
	 void PrimaryAttack();
	 void Idle();
};


class CSL68: public CPaintballGun
{
public:
	void Spawn();
	void Precache();
	void Deploy(int showanim);
	void PrimaryAttack();
	void SecondaryAttack();
	void Idle();
};
class CPhantom: public CPaintballGun
{
public:
	void Spawn();
	void Precache();
	void Deploy(int showanim);
	void PrimaryAttack();
	void SecondaryAttack();
	void Idle();
};

class CPaintBall: public CBaseEntity
{
public:
	void Spawn();
	void Touch(CBaseEntity *pOther);
	void Think();
	void Precache();
};

extern unsigned short g_usPaintball;
void FirePaintball(float *origin,float *velocity,int owner);
void RemoveBalls(int owner);
void RunPaintballs();
#endif 

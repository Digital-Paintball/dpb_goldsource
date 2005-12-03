#ifndef CWEAPON_H
#define CWEAPON_H
#include"event_api.h"
#include"buy.h"

#define WPN_SOUND(x) gEngfuncs.pEventAPI->EV_PlaySound( gEngfuncs.GetLocalPlayer()->index, v_origin, CHAN_WEAPON, x, gEngfuncs.pfnRandomFloat(0.92, 1.0), ATTN_NORM, 0, 98 + gEngfuncs.pfnRandomLong( 0, 3 ))

void CL_PunchAxes(float f);
class ClientWeapon
{
public:
	ClientWeapon(){ m_flIdle=m_flPrimaryAttack=m_flSecondaryAttack=m_flReload=0.0f; m_iReload=0;m_bPrimaryAttack=m_bSecondaryAttack=1;}
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Idle();
	virtual void Frame(double dt);
	virtual void Reload();
	void DefReload(int aidle,int abegin);
	void IdleHandleReload(int arld,int aend);
	void PaintballFire(float max);
	void SetAnim(int anim);
	void Reset();
	float m_flIdle;
	float m_flPrimaryAttack;
	float m_flSecondaryAttack;
	float m_flReload;
	
	int m_bGunDown;
	int m_iReload;
	int m_bPrimaryAttack;
	int m_bSecondaryAttack;

};
class CM98: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class COmen: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};

class CBlazer: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CA5: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};


class CDM4: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};

class CAngel: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CImpulse: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};

class CTimmy: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CShocker: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CBush: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CMatrix: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CCocker: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};

class COrracle: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};


class CSpyder: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};

class CMag: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CExcal: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CEmag: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void Idle();
	virtual void Reload();
};


class CSL68: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Idle();
	virtual void Reload();
};
class CPhantom: public ClientWeapon
{
public:
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Idle();
	virtual void Reload();
};

void FirePaintball(float *origin,float *velocity,int owner,int color);
void RunPaintballs(float time);
void UTIL_Normalize(float *v);
extern vec3_t v_origin,v_angles;
extern ClientWeapon *weapons[WEAPON_MAX];
extern int g_Buttons,g_Random;
void DPB_Seed(unsigned int seed);
float DPB_RandomFloat(float low, float high );
#endif

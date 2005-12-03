#include"pbgun.h"
#include"player.h"
#include"rules.h"
#include"buy.h"
extern int gmsgCurMarker;
void CPaintballGun::Spawn()
{
	
}
void CPaintballGun::DefSpawn()
{
	pev->movetype=MOVETYPE_TOSS;
	pev->solid=SOLID_TRIGGER;
	pev->owner=NULL;
	pev->takedamage=DAMAGE_NO;
	pev->avelocity[1]=90;
	SetThink(NULL);
	SetTouch(&CPaintballGun::Touch);
}

void CPaintballGun::Deploy(int showanim)
{
}

void CPaintballGun::Holster()
{
	player->m_fDeployed=0;
	player->pev->weaponmodel=0;
	player->pev->viewmodel=0;
	MESSAGE_BEGIN(MSG_ONE,gmsgCurMarker,0,player->pev);
		WRITE_BYTE(0xFF);
	MESSAGE_END();
}
#define Length(a) (sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]))
void CPaintballGun::PaintballFire(float max)
{	
	UTIL_MakeVectors(player->pev->v_angle);
	Vector Gunpos=player->GetGunPosition();
	float sr,su;
	player->Seed();

	max*=gBarrels[player->m_iBarrel].scale;
	su=Length(player->pev->velocity);
	if(player->pev->iuser4&U_PRONING) 
		max+=0.5*su;
	else if(player->pev->view_ofs[2]>28.0f) 
		max+=5.0+su*0.25;
	else
		max+=3.0+su*0.88;
	if(!(player->pev->flags&FL_ONGROUND))
		max+=150.0f;
	sr=player->RandomFloat(-max,max)/1000.0;
	su=player->RandomFloat(-max,max)/1000.0;
	vecmul(gpGlobals->v_right,sr);
	vecmul(gpGlobals->v_up,su);
	vecadd(gpGlobals->v_forward,gpGlobals->v_right);
	vecadd(gpGlobals->v_forward,gpGlobals->v_up);
	UTIL_Normalize(gpGlobals->v_forward);
	FirePaintball(Gunpos,gpGlobals->v_forward,player->entindex());
	PLAYBACK_EVENT_FULL(FEV_NOTHOST,player->edict(),g_usPaintball,0.0f,Gunpos,player->pev->v_angle/*+player->pev->punchangle*/,sr*1000.0f,su*1000.0f,m_iId,player->m_iColor,0,0);
	if(!gRules.m_bPrestart)
		m_iHopper--;
}

void CPaintballGun::Touch(CBaseEntity *pOther)
{
	if(!pOther->IsPlayer()||pOther->pev->solid==SOLID_NOT)
		return;
	CBasePlayer* pPlayer=(CBasePlayer*)pOther;
	if(pPlayer->IsSpectator()||pPlayer->m_weapon)
		return;
	GiveToPlayer(pPlayer);
}

void CPaintballGun::GiveToPlayer(CBasePlayer *pPlayer)
{
	SetTouch(NULL);
	player=pPlayer;
	m_iHopper=200;
	player->m_weapon=this;
	pev->effects|=EF_NODRAW;
	pev->solid=SOLID_NOT;
	pev->movetype=MOVETYPE_FOLLOW;
	pev->aiment=pPlayer->edict();
	Deploy(1);
}
void CPaintballGun::DefDeploy(int seq,char *v_model,char* p_model,int showanim)
{
	player->m_fDeployed=1;
	player->pev->viewmodel = MAKE_STRING(v_model);
	player->pev->weaponmodel = MAKE_STRING(p_model);
	if(showanim) {
		MESSAGE_BEGIN( MSG_ONE, SVC_WEAPONANIM, NULL, player->pev );
			WRITE_BYTE( seq );						// sequence number
			WRITE_BYTE( player->m_iBarrel );					// weaponmodel bodygroup.
		MESSAGE_END();
	}
	MESSAGE_BEGIN(MSG_ONE,gmsgCurMarker,0,player->pev);
		WRITE_BYTE(m_iId);
	MESSAGE_END();
	m_flPrimaryAttack=1.0f;
	m_flIdle=1.0f;
	m_flSecondaryAttack=1.0f;
	m_flReload=1.0f;
	m_bPrimaryAttack=1;
	m_bSecondaryAttack=1;
	m_iReload=0;

}
void CPaintballGun::IdleHandleReload()
{
	if(m_iReload&1)
	{
		m_flReload=0;
		m_iReload=0;
	}
	else if(m_iReload==2)
	{
		m_flReload=2.0f;
		m_flPrimaryAttack=2.0f;
		m_flSecondaryAttack=2.0f;
		m_iReload=3;
		m_flIdle=2.0f;
    player->SetAnimation(PLAYER_WALK);
	}
	if((!player->m_iTube)&&player->m_iFullTubes)
	{
		player->m_iTube=100;
		player->m_iFullTubes--;
	}
}


void CPaintballGun::WeaponPostThink()
{
	if( (player->pev->button & IN_RELOAD) && m_flReload<=0 && m_iHopper<200&& player->m_iTube)
		Reload();
	else if(gRules.m_RoundState && (player->pev->button & IN_ATTACK ) && (!(player->pev->button&IN_RELOAD))  && m_flPrimaryAttack<=0 && m_bPrimaryAttack && m_iHopper>0)
		PrimaryAttack();
	else if(gRules.m_RoundState && (player->pev->button & IN_ATTACK2) && (!(player->pev->button&IN_RELOAD)) && m_flSecondaryAttack<=0 && m_bSecondaryAttack )
		SecondaryAttack();
	else if(m_flIdle<=0.0 && (!(player->pev->button&(IN_ATTACK|IN_ATTACK2))) && ((!(player->pev->button&IN_RELOAD))||m_iHopper==200||!player->m_iTube))
		Idle();
	m_flPrimaryAttack-=gpGlobals->frametime;
	m_flSecondaryAttack-=gpGlobals->frametime;
	m_flIdle-=gpGlobals->frametime;
	m_flReload-=gpGlobals->frametime;
}
void CPaintballGun::Idle()
{
	

}

void CPaintballGun::PrimaryAttack()
{

}

void CPaintballGun::SecondaryAttack()
{
}
#ifdef min
#undef min
#endif
#define min(a,b) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
void CPaintballGun::Reload()
{
	if(!m_iReload)
	{
		m_iReload=1;
		m_flReload=2.0f;
		m_flIdle=0.0f;
		m_flPrimaryAttack=2.0f;
		m_flSecondaryAttack=2.0f;
		m_bPrimaryAttack=0;
		m_bSecondaryAttack=0;
	}
	else
	{
		m_iReload=2;
		int sub=min(5,min(player->m_iTube,200-m_iHopper));
		player->m_iTube-=sub;
		m_iHopper+=sub;
		m_flReload=0.1;
	}

}

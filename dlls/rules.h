#ifndef RULES_H
#define RULES_H
#define ROUND_FREEZE 0
#define ROUND_ACTIVE 1
#define ROUND_OVER 2
#define WIN_DRAW 0
#define WIN_RED 1
#define WIN_BLUE 2
#include"object.h"
#include"voice_gamemgr.h"


class CDpbVoice : public IVoiceGameMgrHelper
{
public:
	virtual bool CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pTalker);
};
class CRules
{
public:
	void Reset();
	void Frame();
	void Intermission();
	void ChangeLevel();
	void EndRound(int reason);
	bool CanTakeDamage(edict_t *victim,edict_t* attacker);
	void PlayerKilled(CBasePlayer *vic,entvars_t *killed,entvars_t *inflictor);
	void SpawnSpot(CBasePlayer *player);
	void InitHUD(CBasePlayer *player);
	void SendMOTD(edict_t *client);
	void ChangeTeam(CBasePlayer *plr,int team);
	void PlayerKilled(CBasePlayer* vic,entvars_t *killer);
	BOOL ClientCommand(CBasePlayer *plr,const char *cmd );
	void CheckWeaponConfig(CBasePlayer *plr,int primary,int barrel,	int pods,int color,int jersey,int mask);

	
	
	
	CObjectSpawner *m_RFlag;
	CObjectSpawner *m_BFlag;
	CObjectSpawner *m_CFlag;
	
	CBaseEntity *red;
	CBaseEntity *blue;
	int m_iRedScore;
	int m_iBlueScore;
	int m_iRounds;
	int GameOver;
	int m_RoundState;
	int m_bPrestart;
	float m_flRoundTime;
	float m_flIntermissionEndTime;
	vec3_t m_vCenter;
	int m_iSpawns;
	vec3_t m_vSpawns;
};
	
extern CRules gRules;
extern CDpbVoice gVoice;
#endif 

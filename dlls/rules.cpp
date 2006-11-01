#include<stdio.h>
#include"extdll.h"
#include"util.h"
#include"player.h"
#include"voice_gamemgr.h"
#include"rules.h"
#include"game.h"
#include"func_break.h"
#include"trains.h"
#include"buy.h"
#include"pm_shared.h"
#include"hltv.h"

CRules *gRules; //Tony; our NEW "global" rule object
#include "paintballs.h"

#define TEAM_NAME(x) ( x == 0 ? "SPECTATOR" : ( x==1 ? "RED" : "BLUE" ) )
CVoiceGameMgr	g_VoiceGameMgr;
extern int gmsgCredits,gmsgTeamScore,gmsgCurMarker,gmsgTimer,gmsgServerName,gmsgDeath,gmsgMOTD,gmsgShowMenu,gmsgScoreInfo,gmsgRespawn, gmsgNewRound;

CDpbVoice gVoice;
void InitializeTransitions();
bool CDpbVoice::CanPlayerHearPlayer(CBasePlayer *pListener,CBasePlayer *pTalker)
{
	if((pTalker->pev->team!=pListener->pev->team) || 
	   (pTalker->pev->deadflag&&!pListener->pev->deadflag))
		return false;
	else
		return true;
	
}
extern int gmsgTextMsg;
void CRules::Reset()
{
	gBallManager.RemoveBalls(-1); //get rid of all ballz0rs
	m_RFlag=0;
	m_BFlag=0;
	m_CFlag=0;
	red=0;
	blue=0;
	m_iRedScore		=	0;
	m_iBlueScore	=	0;
	m_iRounds		=	0;
	GameOver		=	0;
	m_iSpawns		=	0;
	m_bPrestart		=	1;
	m_RoundState=ROUND_ACTIVE;
	m_flIntermissionEndTime=0;
	InitializeTransitions();
	if ( IS_DEDICATED_SERVER() )
	{
		char *servercfgfile = (char *)CVAR_GET_STRING( "servercfgfile" );
		if ( servercfgfile && servercfgfile[0] )
		{
			char szCommand[256];
			
			ALERT( at_console, "Executing dedicated server config file\n" );
			sprintf( szCommand, "exec %s\n", servercfgfile );
			SERVER_COMMAND( szCommand );
		}
	}
	else
	{
			char *lservercfgfile = (char *)CVAR_GET_STRING( "lservercfgfile" );

		if ( lservercfgfile && lservercfgfile[0] )
		{
			char szCommand[256];
			
			ALERT( at_console, "Executing listen server config file\n" );
			sprintf( szCommand, "exec %s\n", lservercfgfile );
			SERVER_COMMAND( szCommand );
		}
	}
	m_vSpawns[0]=m_vSpawns[1]=m_vSpawns[2]=0;
	red=0;
	blue=0;
	m_flRoundTime=gpGlobals->time+mp_warmuptime.value;
	g_VoiceGameMgr.Init(&gVoice, gpGlobals->maxClients);


}
void CRules::CheckWeaponConfig(CBasePlayer *plr, int primary,int barrel,int pods,int color,int jersey,int mask) 
{
	if( primary < 0 || primary>=WEAPON_MAX )
		return;
	if( barrel < 0 || barrel >= BARREL_MAX )
		return;
	if( pods<0 || pods >MAX_PODS )
		return;
	if( gWeapons[primary].cost + gBarrels[barrel].cost + pods * COST_POD > plr->credits)
		return;
	if(color<0 || color>6 || jersey<0 || jersey>=JERSEY_MAX || mask<0 || mask >= MASK_MAX )
		return;
	plr->ConfigWeapons( primary, barrel, pods, color, jersey, mask );
	if( ( !plr->IsSpectator() ) && ( m_bPrestart || m_RoundState==ROUND_FREEZE || !plr->m_fDeployed ) )
		plr->ExecConfig();


}
BOOL CRules::ClientCommand(CBasePlayer *plr,const char *cmd)
{
	if (strcmp(cmd, "menuselect" )==0)
	{
		if(CMD_ARGC()!=2)
			return TRUE;
		int slot = atoi( CMD_ARGV(1) );

		if(plr->m_Menu==MENU_TEAM)
		{
			if(slot==10)
				return TRUE;
			else if(slot==1)
				ChangeTeam(plr,TEAM_RED);
			else if(slot==2)
				ChangeTeam(plr,TEAM_BLUE);
			else if(slot==3)
				ChangeTeam(plr,TEAM_SPEC);
			plr->m_Menu=MENU_NONE;
		}
		
	    
		return TRUE;
	}
	else if(strcmp(cmd,"jointeam")==0)
	{
		if(CMD_ARGC()!=2)
			return TRUE;
		int t=atoi(CMD_ARGV(1));
		if(t<0 || t>3 || (plr->pev->team==t && ( t!=0 || plr->pev->deadflag==DEAD_RESPAWNABLE)))
			return TRUE;
		if(t==3)
		{
			int numred=0,numblue=0;
			edict_t *e;
			for(int i=1;i<=gpGlobals->maxClients;i++)
			{
				e=INDEXENT(i);
				if((!e)||e->free)
					continue;
				if(e->v.team==TEAM_BLUE)
					numblue++;
				else if(e->v.team==TEAM_RED)
					numred++;
			}
			if(numred>numblue)
				t=2;
			else
				t=1;
		}
		ChangeTeam(plr,t);
		if( plr->m_fSendWeaponMenu && t!=0 ) 
		{
			plr->m_fSendWeaponMenu=0;
			UTIL_ShowVgui(plr->pev,30);
		}
		return TRUE;
	}
	else if(strcmp(cmd,"dropflag")==0)
	{
		plr->DropFlag(1);
		return TRUE;
	}
	else if(!strcmp(cmd,"vgui"))
	{
		if(CMD_ARGC()!=2)
			return TRUE;
		UTIL_ShowVgui(plr->pev,atoi(CMD_ARGV(1)));
		return TRUE;
	}
	else if(!strcmp(cmd,"follownext"))
	{
		if(plr->pev->iuser1==OBS_CHASE_FREE
		|| plr->pev->iuser1==OBS_CHASE_LOCKED
		|| plr->pev->iuser1==OBS_IN_EYE)
		{	
			if(CMD_ARGC()>=2&&atoi(CMD_ARGV(1)))
				plr->Spectator_FindNextPlayer(1);
			else
				plr->Spectator_FindNextPlayer(0);
		}
		return TRUE;
	}
	else if(!strcmp(cmd,"specmode"))
	{
		if(plr->pev->iuser1&&CMD_ARGC()==2)
			plr->Spectator_SetMode(atoi(CMD_ARGV(1)));
		return TRUE;
	}
	else if(!strcmp(cmd, "weaponconfig")) 
	{
		int i=CMD_ARGC();
		if(i!=7) 
			return TRUE;

		CheckWeaponConfig( plr, 
			atoi(CMD_ARGV(1)), 
			atoi(CMD_ARGV(2)), 
			atoi(CMD_ARGV(3)), 
			atoi(CMD_ARGV(4)), 
			atoi(CMD_ARGV(5)), 
			atoi(CMD_ARGV(6)));
		return TRUE;
	}
	else {
		return FALSE;
	}
}
void CRules::SendMOTD( edict_t *client )
{
	MESSAGE_BEGIN( MSG_ONE, gmsgServerName, NULL, client );
		WRITE_STRING( CVAR_GET_STRING("hostname") );
	MESSAGE_END();
	int size;
	char *file,*file2;
	char buf[65];
	buf[64]='\0';
	file2=file = (char*)g_engfuncs.pfnLoadFileForMe((char*)CVAR_GET_STRING("motdfile"),&size);
	if(file)	{
		for(;size>64;size-=64,file+=64)
		{
			strncpy(buf,file,64);
			MESSAGE_BEGIN( MSG_ONE, gmsgMOTD, NULL, client );
				WRITE_BYTE(FALSE);
				WRITE_STRING(buf );
			MESSAGE_END();
			
		}
		MESSAGE_BEGIN(MSG_ONE,gmsgMOTD,NULL,client);
			WRITE_BYTE(TRUE);
		if(size)
			WRITE_STRING(file);
		else
			WRITE_STRING(" ");
		MESSAGE_END();
		g_engfuncs.pfnFreeFile(file2);
	}
	else 
		ALERT( at_console, "Unable to Load MOTD file, %s\n",CVAR_GET_STRING("motdfile"));
	MESSAGE_BEGIN(MSG_ONE,gmsgTimer,NULL,client);
		WRITE_BYTE(m_RoundState);
		if(m_bPrestart)
			WRITE_SHORT(0);
		else
			WRITE_SHORT((int)(m_flRoundTime-gpGlobals->time));
	MESSAGE_END();
	MESSAGE_BEGIN( MSG_ONE, gmsgMOTD, NULL, client );
		WRITE_BYTE(TRUE);
		WRITE_STRING("\n");
	MESSAGE_END();
}
void CRules::Intermission()
{
	if(GameOver )
		return;
	MESSAGE_BEGIN(MSG_ALL, SVC_INTERMISSION);
	MESSAGE_END();
	m_flIntermissionEndTime=gpGlobals->time+mp_chattime.value;
	GameOver=1;
}
//BEGIN Tony; merge from sdk 2.2

#define MAX_RULE_BUFFER 1024

typedef struct mapcycle_item_s
{
	struct mapcycle_item_s *next;

	char mapname[ 32 ];
	int  minplayers, maxplayers;
	char rulebuffer[ MAX_RULE_BUFFER ];
} mapcycle_item_t;

typedef struct mapcycle_s
{
	struct mapcycle_item_s *items;
	struct mapcycle_item_s *next_item;
} mapcycle_t;

/*
==============
DestroyMapCycle

Clean up memory used by mapcycle when switching it
==============
*/
void DestroyMapCycle( mapcycle_t *cycle )
{
	mapcycle_item_t *p, *n, *start;
	p = cycle->items;
	if ( p )
	{
		start = p;
		p = p->next;
		while ( p != start )
		{
			n = p->next;
			delete p;
			p = n;
		}
		
		delete cycle->items;
	}
	cycle->items = NULL;
	cycle->next_item = NULL;
}

static char com_token[ 1500 ];

/*
==============
COM_Parse

Parse a token out of a string
==============
*/
char *COM_Parse (char *data)
{
	int             c;
	int             len;
	
	len = 0;
	com_token[0] = 0;
	
	if (!data)
		return NULL;
		
// skip whitespace
skipwhite:
	while ( (c = *data) <= ' ')
	{
		if (c == 0)
			return NULL;                    // end of file;
		data++;
	}
	
// skip // comments
	if (c=='/' && data[1] == '/')
	{
		while (*data && *data != '\n')
			data++;
		goto skipwhite;
	}
	

// handle quoted strings specially
	if (c == '\"')
	{
		data++;
		while (1)
		{
			c = *data++;
			if (c=='\"' || !c)
			{
				com_token[len] = 0;
				return data;
			}
			com_token[len] = c;
			len++;
		}
	}

// parse single characters
	if (c=='{' || c=='}'|| c==')'|| c=='(' || c=='\'' || c == ',' )
	{
		com_token[len] = c;
		len++;
		com_token[len] = 0;
		return data+1;
	}

// parse a regular word
	do
	{
		com_token[len] = c;
		data++;
		len++;
		c = *data;
	if (c=='{' || c=='}'|| c==')'|| c=='(' || c=='\'' || c == ',' )
			break;
	} while (c>32);
	
	com_token[len] = 0;
	return data;
}

/*
==============
COM_TokenWaiting

Returns 1 if additional data is waiting to be processed on this line
==============
*/
int COM_TokenWaiting( char *buffer )
{
	char *p;

	p = buffer;
	while ( *p && *p!='\n')
	{
		if ( !isspace( *p ) || isalnum( *p ) )
			return 1;

		p++;
	}

	return 0;
}



/*
==============
ReloadMapCycleFile


Parses mapcycle.txt file into mapcycle_t structure
==============
*/
int ReloadMapCycleFile( char *filename, mapcycle_t *cycle )
{
	char szBuffer[ MAX_RULE_BUFFER ];
	char szMap[ 32 ];
	int length;
	char *pFileList;
	char *aFileList = pFileList = (char*)LOAD_FILE_FOR_ME( filename, &length );
	int hasbuffer;
	mapcycle_item_s *item, *newlist = NULL, *next;

	if ( pFileList && length )
	{
		// the first map name in the file becomes the default
		while ( 1 )
		{
			hasbuffer = 0;
			memset( szBuffer, 0, MAX_RULE_BUFFER );

			pFileList = COM_Parse( pFileList );
			if ( strlen( com_token ) <= 0 )
				break;

			strcpy( szMap, com_token );

			// Any more tokens on this line?
			if ( COM_TokenWaiting( pFileList ) )
			{
				pFileList = COM_Parse( pFileList );
				if ( strlen( com_token ) > 0 )
				{
					hasbuffer = 1;
					strcpy( szBuffer, com_token );
				}
			}

			// Check map
			if ( IS_MAP_VALID( szMap ) )
			{
				// Create entry
				char *s;

				item = new mapcycle_item_s;

				strcpy( item->mapname, szMap );

				item->minplayers = 0;
				item->maxplayers = 0;

				memset( item->rulebuffer, 0, MAX_RULE_BUFFER );

				if ( hasbuffer )
				{
					s = g_engfuncs.pfnInfoKeyValue( szBuffer, "minplayers" );
					if ( s && s[0] )
					{
						item->minplayers = atoi( s );
						item->minplayers = max( item->minplayers, 0 );
						item->minplayers = min( item->minplayers, gpGlobals->maxClients );
					}
					s = g_engfuncs.pfnInfoKeyValue( szBuffer, "maxplayers" );
					if ( s && s[0] )
					{
						item->maxplayers = atoi( s );
						item->maxplayers = max( item->maxplayers, 0 );
						item->maxplayers = min( item->maxplayers, gpGlobals->maxClients );
					}

					// Remove keys
					//
					g_engfuncs.pfnInfo_RemoveKey( szBuffer, "minplayers" );
					g_engfuncs.pfnInfo_RemoveKey( szBuffer, "maxplayers" );

					strcpy( item->rulebuffer, szBuffer );
				}

				item->next = cycle->items;
				cycle->items = item;
			}
			else
			{
				ALERT( at_console, "Skipping %s from mapcycle, not a valid map\n", szMap );
			}

		}

		FREE_FILE( aFileList );
	}

	// Fixup circular list pointer
	item = cycle->items;

	// Reverse it to get original order
	while ( item )
	{
		next = item->next;
		item->next = newlist;
		newlist = item;
		item = next;
	}
	cycle->items = newlist;
	item = cycle->items;

	// Didn't parse anything
	if ( !item )
	{
		return 0;
	}

	while ( item->next )
	{
		item = item->next;
	}
	item->next = cycle->items;
	
	cycle->next_item = item->next;

	return 1;
}

/*
==============
CountPlayers

Determine the current # of active players on the server for map cycling logic
==============
*/
int CountPlayers( void )
{
	int	num = 0;

	for ( int i = 1; i <= gpGlobals->maxClients; i++ )
	{
		CBaseEntity *pEnt = UTIL_PlayerByIndex( i );

		if ( pEnt )
		{
			num = num + 1;
		}
	}

	return num;
}

/*
==============
ExtractCommandString

Parse commands/key value pairs to issue right after map xxx command is issued on server
 level transition
==============
*/
void ExtractCommandString( char *s, char *szCommand )
{
	// Now make rules happen
	char	pkey[512];
	char	value[512];	// use two buffers so compares
								// work without stomping on each other
	char	*o;
	
	if ( *s == '\\' )
		s++;

	while (1)
	{
		o = pkey;
		while ( *s != '\\' )
		{
			if ( !*s )
				return;
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value;

		while (*s != '\\' && *s)
		{
			if (!*s)
				return;
			*o++ = *s++;
		}
		*o = 0;

		strcat( szCommand, pkey );
		if ( strlen( value ) > 0 )
		{
			strcat( szCommand, " " );
			strcat( szCommand, value );
		}
		strcat( szCommand, "\n" );

		if (!*s)
			return;
		s++;
	}
}
//END Tony; merge from sdk 2.2
void CRules::ChangeLevel()
{
	static char szPreviousMapCycleFile[ 256 ];
	static mapcycle_t mapcycle;

	char szNextMap[32];
	char szFirstMapInList[32];
	char szCommands[ 1500 ];
	char szRules[ 1500 ];
	int minplayers = 0, maxplayers = 0;
	strcpy( szFirstMapInList, "hldm1" );  // the absolute default level is hldm1

	int	curplayers;
	BOOL do_cycle = TRUE;

	// find the map to change to
	char *mapcfile = (char*)CVAR_GET_STRING( "mapcyclefile" );
	ASSERT( mapcfile != NULL );

	szCommands[ 0 ] = '\0';
	szRules[ 0 ] = '\0';

	curplayers = CountPlayers();

	// Has the map cycle filename changed?
	if ( stricmp( mapcfile, szPreviousMapCycleFile ) )
	{
		strcpy( szPreviousMapCycleFile, mapcfile );

		DestroyMapCycle( &mapcycle );

		if ( !ReloadMapCycleFile( mapcfile, &mapcycle ) || ( !mapcycle.items ) )
		{
			ALERT( at_console, "Unable to load map cycle file %s\n", mapcfile );
			do_cycle = FALSE;
		}
	}

	if ( do_cycle && mapcycle.items )
	{
		BOOL keeplooking = FALSE;
		BOOL found = FALSE;
		mapcycle_item_s *item;

		// Assume current map
		strcpy( szNextMap, STRING(gpGlobals->mapname) );
		strcpy( szFirstMapInList, STRING(gpGlobals->mapname) );

		// Traverse list
		for ( item = mapcycle.next_item; item->next != mapcycle.next_item; item = item->next )
		{
			keeplooking = FALSE;

			ASSERT( item != NULL );

			if ( item->minplayers != 0 )
			{
				if ( curplayers >= item->minplayers )
				{
					found = TRUE;
					minplayers = item->minplayers;
				}
				else
				{
					keeplooking = TRUE;
				}
			}

			if ( item->maxplayers != 0 )
			{
				if ( curplayers <= item->maxplayers )
				{
					found = TRUE;
					maxplayers = item->maxplayers;
				}
				else
				{
					keeplooking = TRUE;
				}
			}

			if ( keeplooking )
				continue;

			found = TRUE;
			break;
		}

		if ( !found )
		{
			item = mapcycle.next_item;
		}			
		
		// Increment next item pointer
		mapcycle.next_item = item->next;

		// Perform logic on current item
		strcpy( szNextMap, item->mapname );

		ExtractCommandString( item->rulebuffer, szCommands );
		strcpy( szRules, item->rulebuffer );
	}

	if ( !IS_MAP_VALID(szNextMap) )
	{
		strcpy( szNextMap, szFirstMapInList );
	}

	GameOver = TRUE;

	ALERT( at_console, "CHANGE LEVEL: %s\n", szNextMap );
	if ( minplayers || maxplayers )
	{
		ALERT( at_console, "PLAYER COUNT:  min %i max %i current %i\n", minplayers, maxplayers, curplayers );
	}
	if ( strlen( szRules ) > 0 )
	{
		ALERT( at_console, "RULES:  %s\n", szRules );
	}
	
	CHANGE_LEVEL( szNextMap, NULL );
	if ( strlen( szCommands ) > 0 )
	{
		SERVER_COMMAND( szCommands );
	}
}

void CRules::Frame()
{
	g_VoiceGameMgr.Update(gpGlobals->frametime);
	if(GameOver)
	{
		if( m_flIntermissionEndTime<=gpGlobals->time )
			ChangeLevel();
		return;
	}

	if(m_bPrestart) 
	{
		if(((int)(m_flRoundTime-gpGlobals->time))<=0)
			UTIL_ClientPrintAll(HUD_PRINTCENTER,"Warm-up time over");
	}

	if(m_RoundState==ROUND_FREEZE)
	{
		damageDisabled = true; //can't take damage when this is set; prevents killing during freeze time, or whatever.
		//Tony; re-worked to check to start a round, based on number of players; no point in starting
		//a round if there are no players on it!!
		if(gpGlobals->time>=m_flRoundTime)
		{
			CBasePlayer *plr;
#if 0
			int numRed = 0, numBlue = 0; //has to be at least one on each team before the round goes out of freeze time.
			//since player's are eliminated cuasing wins, there has to be a team before it can be either a draw
			//or an opposing team win.

			//todo; take the CS / FLF 2.0 approach; with the "practice" one-player on one-team round.
			for(int i=1;i<=gpGlobals->maxClients;i++)
			{
				plr=(CBasePlayer*)UTIL_PlayerByIndex(i);
				if (plr)
				{
					if (plr->pev->team == TEAM_BLUE)
						numBlue++;
					if (plr->pev->team == TEAM_RED)
						numRed++;
				}
			}

			if (numRed > 0 && numBlue > 0)
			{
#endif
				for(int i=1;i<=gpGlobals->maxClients;i++)
				{
					plr=(CBasePlayer*)UTIL_PlayerByIndex(i);
					if(plr&&plr->pev->team!=TEAM_SPEC)
					{
						g_engfuncs.pfnSetClientMaxspeed(plr->edict(),1000);
						plr->pev->takedamage=DAMAGE_YES;
					}
				}
				m_flRoundTime=gpGlobals->time+mp_roundtime.value;
				m_RoundState=ROUND_ACTIVE;
				//start round
				UTIL_ClientPrintAll(HUD_PRINTCENTER, "Round Begin!\n");
				damageDisabled = false; //take damage again.
#if 0
			}
			else //do another 5 seconds of warmup time
			{
				m_flRoundTime = gpGlobals->time + mp_freezetime.value;
				UTIL_ClientPrintAll(HUD_PRINTCENTER, "Each team must have at least one player before the round will start.\nResetting Warmup.");
			}
#endif
			MESSAGE_BEGIN(MSG_ALL,gmsgTimer,NULL);
				WRITE_BYTE(m_RoundState);
				WRITE_SHORT((int)mp_roundtime.value);
			MESSAGE_END();
		}
	}
	else if ( m_RoundState == ROUND_ACTIVE )
	{
		//why is this ending on pre-start ? shouldn't it just keep going? .. 
		//okay i get it now. if it's prestart or roundtime is > 0, and roundtime < time, end
		//then do it; otherwise it wont.
		//makes sense now.
		//so if mp_roundtime is 0, it wont end the round, but it will end the round if prestart is set.
		if ( ( m_bPrestart || mp_roundtime.value > 0 ) && m_flRoundTime <= gpGlobals->time )
			EndRound(WIN_DRAW);
	}
	else
	{
		//if we're not in freeze, or active time; this should function.
		if ( m_flRoundTime <= gpGlobals->time )
		{
			damageDisabled = true; //can't take damage when this is set; prevents killing during freeze time, or whatever.

			float time=mp_timelimit.value*60;
			int rnds=(int)mp_roundlimit.value;

//			ALERT(at_console, "m_iRounds i\n", m_iRounds);
			if((time > 0 && gpGlobals->time >= time) || (rnds> 0 && m_iRounds >= rnds))
			{
				Intermission();
				return;
			}

			CBasePlayer *plr;
			m_RoundState=ROUND_FREEZE;
			m_flRoundTime=gpGlobals->time+mp_freezetime.value;

			MESSAGE_BEGIN(MSG_ALL,gmsgTimer,NULL);
				WRITE_BYTE(m_RoundState);
				WRITE_SHORT((int)mp_freezetime.value);
			MESSAGE_END();

			if(mp_changeteams.value) 
			{
				int tmp=m_iRedScore;
				m_iRedScore=m_iBlueScore;
				m_iBlueScore=tmp;
				MESSAGE_BEGIN(MSG_ALL,gmsgTeamScore,NULL);
					WRITE_BYTE(m_iRedScore);
					WRITE_BYTE(m_iBlueScore);
				MESSAGE_END();
			}
			for(int i=1;i<=gpGlobals->maxClients;i++)
			{
				plr=(CBasePlayer*)UTIL_PlayerByIndex(i);
				if(!plr)
					continue;

				if(!m_bPrestart) 
					plr->credits+=(int)mp_roundcredits.value;

				if(plr->credits>(int)mp_maxcredits.value)
						plr->credits=(int)mp_maxcredits.value;

				MESSAGE_BEGIN(MSG_ONE,gmsgCredits,NULL,plr->edict());
					WRITE_BYTE(plr->credits);
				MESSAGE_END();

				if(plr->pev->team!=TEAM_SPEC)
				{
					plr->StopSpectating();
					if(mp_changeteams.value)
					{
						if(plr->pev->team==TEAM_RED)
							ChangeTeam(plr,TEAM_BLUE);
						else
							ChangeTeam(plr,TEAM_RED);
					}
					plr->DropFlag(0);
					plr->ExecConfig();
					plr->Spawn();

					MESSAGE_BEGIN( MSG_ONE, gmsgNewRound, NULL, plr->pev );
					MESSAGE_END();

					g_engfuncs.pfnSetClientMaxspeed(plr->edict(),0.00001);
				}
			}
			if(m_bPrestart) 
			{
				m_bPrestart=0;
				m_iRounds=0;
			}
			if(m_CFlag&&!FNullEnt(m_CFlag->edict()))
			{
				m_CFlag->Flag(m_CFlag->pev->team);
			}
			if(m_RFlag&&!FNullEnt(m_RFlag->edict()))
			{
				m_RFlag->Flag(m_RFlag->pev->team);
			}
			if(m_BFlag&&!FNullEnt(m_BFlag->edict()))
			{
				m_BFlag->Flag(m_BFlag->pev->team);
			}
			CBreakable *door =(CBreakable*)UTIL_FindEntityByClassname(NULL, "func_breakable");
			while (door)
			{
				door->Spawn();
				door =(CBreakable*)UTIL_FindEntityByClassname(door, "func_breakable");
			}
			CFuncTrackTrain *dor =(CFuncTrackTrain*)UTIL_FindEntityByClassname(NULL, "func_tracktrain");
			while (dor)
			{
				dor->Restart();
				dor =(CFuncTrackTrain*)UTIL_FindEntityByClassname(dor, "func_tracktrain");
			}
			CFuncTrain *dr =(CFuncTrain*)UTIL_FindEntityByClassname(NULL, "func_train");
			while (dr)
			{
				dr->Restart();
				dr =(CFuncTrain*)UTIL_FindEntityByClassname(dr, "func_train");
			}
			m_iRounds++;
		}
	}
}
extern int gmsgTeamInfo;
extern void ClientKill(edict_t *pEntity);
void CRules::ChangeTeam(CBasePlayer *plr,int team)
{
	plr->pev->team=team;
	MESSAGE_BEGIN( MSG_ALL, gmsgScoreInfo);
		WRITE_BYTE( ENTINDEX(plr->edict()) );
		WRITE_SHORT( plr->pev->frags );
		WRITE_SHORT( plr->m_iDeaths );
		WRITE_SHORT( 0 );
		WRITE_SHORT(plr->pev->team);
	MESSAGE_END();
	switch(team)
	{
	case TEAM_RED:
		plr->pev->skin=(plr->pev->skin)&6;
		break;
	case TEAM_BLUE:
		plr->pev->skin=(plr->pev->skin&6)+1;
		break;
	default:
		plr->StartSpectating(plr->pev->origin,plr->pev->v_angle);
		plr->m_flSpawnTime=0;
		break;
	}

	if ( plr->pev->team != TEAM_SPEC )
	{
		if ( m_bPrestart || m_RoundState == ROUND_FREEZE || mp_respawntime.value == 0.0f )
		{
			plr->StopSpectating();
			plr->Spawn();
			if(m_RoundState==ROUND_FREEZE)
			{
				g_engfuncs.pfnSetClientMaxspeed(plr->edict(),0.00001);
				plr->pev->takedamage=DAMAGE_NO;
			}
			else
			{
				plr->pev->takedamage=DAMAGE_YES;
				g_engfuncs.pfnSetClientMaxspeed(plr->edict(),1000.0f);
			}
		}
		else if ( !plr->pev->deadflag )
		{
			plr->pev->health=0;
			ClientKill(plr->edict());
			plr->m_iDeaths--;
		} else 
			plr->StartSpectating(plr->pev->origin,plr->pev->v_angle);
	}
	edict_t *e;
	int numred=0,numblue=0;
	for(int i=1;i<=gpGlobals->maxClients;i++)
	{
		e=INDEXENT(i);
		if((!e)||e->free)
			continue;
		if(e->v.team==TEAM_BLUE && !e->v.deadflag)
			numblue++;
		else if(e->v.team==TEAM_RED && !e->v.deadflag)
			numred++;
	}
	if((!m_bPrestart)&&((!numred)||(!numblue)))
		EndRound(WIN_DRAW);
}


void CRules::InitHUD(CBasePlayer *pl)
{
	pl->pev->frags=pl->m_iDeaths=0;
	pl->credits=(int)mp_startcredits.value+m_iRounds*(int)mp_roundcredits.value;
	if(pl->credits>(int)mp_maxcredits.value)
			pl->credits=(int)mp_maxcredits.value;
	UTIL_ClientPrintAll( HUD_PRINTTALK, UTIL_VarArgs( "\xf0* %s has joined the game\n", 
		( pl->pev->netname && STRING(pl->pev->netname)[0]) ? STRING(pl->pev->netname) : "unconnected" ) );
	UTIL_LogPrintf( "\"%s<%i><%s><%i>\" entered the game\n",  
			STRING( pl->pev->netname ), 
			GETPLAYERUSERID( pl->edict() ),
			GETPLAYERAUTHID( pl->edict() ),
			pl->pev->team);
	MESSAGE_BEGIN( MSG_ALL, gmsgScoreInfo);
		WRITE_BYTE( ENTINDEX(pl->edict()) );
		WRITE_SHORT( 0 );
		WRITE_SHORT( 0 );
		WRITE_SHORT( 0 );
		WRITE_SHORT( 0 );
	MESSAGE_END();
	MESSAGE_BEGIN(MSG_ONE,gmsgCredits,NULL,pl->edict());
		WRITE_BYTE(pl->credits);
	MESSAGE_END();
	MESSAGE_BEGIN(MSG_ONE,gmsgCurMarker,NULL,pl->pev);
		WRITE_BYTE(255);
	MESSAGE_END();
	//Tony; cleaned this up
	MESSAGE_BEGIN(MSG_ONE,gmsgTeamScore,NULL,pl->edict());
		WRITE_BYTE(m_iRedScore);
		WRITE_BYTE(m_iBlueScore);
	MESSAGE_END();
	SendMOTD( pl->edict() );
	for ( int i = 1; i <= gpGlobals->maxClients; i++ )
	{
		CBasePlayer *plr = (CBasePlayer *)UTIL_PlayerByIndex( i );
		if ( plr )
		{
			MESSAGE_BEGIN( MSG_ONE, gmsgScoreInfo, NULL, pl->edict());
				WRITE_BYTE( i );
				WRITE_SHORT( plr->pev->frags );
				WRITE_SHORT( plr->m_iDeaths );
				WRITE_SHORT( 0 );
				WRITE_SHORT(plr->pev->team);
			MESSAGE_END();
			if(plr->pev->deadflag)
			{
				MESSAGE_BEGIN( MSG_ONE, gmsgDeath, NULL, pl->edict());
					WRITE_BYTE(0xff);
					WRITE_BYTE(i);
					WRITE_STRING("a");
				MESSAGE_END();
			}
		}
	}
	g_engfuncs.pfnSetClientMaxspeed(pl->edict(),0.00001);
	pl->m_iClientTube=pl->m_iClientFullTubes=pl->m_iClientHopper=pl->m_iPrimary=pl->m_iPrimaryCommand= pl->m_iBarrel=pl->m_iBarrelCommand=-1;
	pl->m_fDeployed=pl->m_iTube=pl->m_iFullTubes=pl->m_iPod=pl->m_iPodCommand=0;
	pl->m_weapon=0;
	pl->pev->movetype=MOVETYPE_NONE;
	pl->pev->solid=SOLID_NOT;
	pl->pev->deadflag=DEAD_DEAD;
	pl->pev->health=0;
	pl->pev->takedamage=DAMAGE_NO;
	pl->pev->iuser1=0;
	pl->pev->iuser2=0;
	pl->pev->effects=EF_NODRAW;
	UTIL_ShowVgui(pl->pev,2);
	pl->m_fSendWeaponMenu=1;
	if(GameOver )
	{
		MESSAGE_BEGIN( MSG_ONE, SVC_INTERMISSION, NULL, pl->edict() );
		MESSAGE_END();
	}
}
void CRules::EndRound(int reason)
{
	if(m_RoundState!=ROUND_ACTIVE)
		return;
	if(!m_bPrestart) {
		switch(reason)
		{
		case WIN_DRAW:
			UTIL_ClientPrintAll(HUD_PRINTCENTER,"Draw!");
			break;
		case WIN_RED:
			m_iRedScore++;
			MESSAGE_BEGIN(MSG_ALL,gmsgTeamScore,NULL);
				WRITE_BYTE(m_iRedScore);
				WRITE_BYTE(m_iBlueScore);
			MESSAGE_END();
			UTIL_ClientPrintAll(HUD_PRINTCENTER,"Red Wins!");
			break;
		case WIN_BLUE:
			m_iBlueScore++;
			MESSAGE_BEGIN(MSG_ALL,gmsgTeamScore,NULL);
				WRITE_BYTE(m_iRedScore);
				WRITE_BYTE(m_iBlueScore);
			MESSAGE_END();
			UTIL_ClientPrintAll(HUD_PRINTCENTER,"Blue Wins!");
			break;
		}
		m_flRoundTime=gpGlobals->time+3.0f;
	}
	else {
		m_flRoundTime=0;
	}
	m_RoundState=ROUND_OVER;
	MESSAGE_BEGIN(MSG_ALL,gmsgTimer,NULL);
		WRITE_BYTE(m_RoundState);
		WRITE_SHORT(0);
	MESSAGE_END();
}
void CRules::SpawnSpot(CBasePlayer *player)
{
	if(player->pev->team==TEAM_RED)
	{
		red=UTIL_FindEntityByClassname(red,"info_playerstart_red");
		if(!red)
		{
			red=UTIL_FindEntityByClassname(red,"info_playerstart_red");
			if(!red)
			{
				ALERT(at_logged,"No Red Spawn Points on map!\n");
				return;
			}
		}
		UTIL_SetOrigin(player->pev,red->pev->origin);
	}
	else
	{
		blue=UTIL_FindEntityByClassname(blue,"info_playerstart_blue");
		if(!blue)
		{
			blue=UTIL_FindEntityByClassname(blue,"info_playerstart_blue");
			if(!blue)
			{
				ALERT(at_logged,"No Blue Spawn Points on map!\n");
				return;
			}
		}
		UTIL_SetOrigin(player->pev,blue->pev->origin);
	}
	player->pev->angles=UTIL_VecToAngles(player->pev->origin-m_vCenter);
	player->pev->angles[0]=0;
	player->pev->v_angle  = g_vecZero;
	player->pev->velocity = g_vecZero;
	player->pev->punchangle = g_vecZero;
	player->pev->fixangle = TRUE;
}
bool CRules::CanTakeDamage(edict_t *victim,edict_t* attacker)
{
	if (damageDisabled)
		return false; //Tony; no damage when it's disabled.
	if(victim->v.deadflag || victim->v.takedamage==DAMAGE_NO||(victim->v.team==attacker->v.team&&mp_friendlyfire.value==0))
		return 0;
	else
		return 1;
}
void CRules::PlayerKilled(CBasePlayer *vic,entvars_t* killer)
{
	if(!vic||!killer)
		return;
	if(!strcmp(STRING(killer->classname),"player")) {
		CBasePlayer *player=(CBasePlayer*)CBaseEntity::Instance(killer);
		if(vic->entindex()!=player->entindex()) {
			UTIL_LogPrintf( "\"%s<%i><%s><%s>\" killed \"%s<%i><%s><%s>\" with \"%s\"\n",  
				STRING( killer->netname ),
				GETPLAYERUSERID(ENT(killer)),
				GETPLAYERAUTHID(ENT(killer)),
				TEAM_NAME(killer->team),
				STRING(vic->pev->netname),
				GETPLAYERUSERID(vic->edict()),
				GETPLAYERAUTHID(vic->edict()),
				TEAM_NAME(vic->pev->team),
				gWeapons[player->m_weapon->m_iId].name);
			if(!m_bPrestart) {
				killer->frags++;
				player->credits+=(int)mp_markcredits.value;
				if(player->credits>(int)mp_maxcredits.value)
						player->credits=(int)mp_maxcredits.value;
				MESSAGE_BEGIN(MSG_ONE,gmsgCredits,NULL,player->edict());
					WRITE_BYTE(player->credits);
				MESSAGE_END();
			}
			player->m_flNextDecalTime = gpGlobals->time;
			MESSAGE_BEGIN( MSG_ALL, gmsgScoreInfo );
				WRITE_BYTE(ENTINDEX(ENT(killer)));
				WRITE_SHORT(killer->frags );
				WRITE_SHORT(player->m_iDeaths );
				WRITE_SHORT( 0 );
				WRITE_SHORT(killer->team);
			MESSAGE_END();
			MESSAGE_BEGIN(MSG_ALL,gmsgDeath);
				WRITE_BYTE(ENTINDEX(ENT(killer)));
				WRITE_BYTE(vic->entindex());
				WRITE_STRING(gWeapons[player->m_weapon->m_iId].name);
			MESSAGE_END();
		} else {
			UTIL_LogPrintf( "\"%s<%i><%s><%s>\" commited suicide with \"killcmd\"\n",
					STRING( killer->netname ),
					GETPLAYERUSERID(ENT(killer)),
					GETPLAYERAUTHID(ENT(killer)),
					TEAM_NAME(killer->team));
			MESSAGE_BEGIN(MSG_ALL,gmsgDeath);
				WRITE_BYTE(vic->entindex());
				WRITE_BYTE(vic->entindex());
				WRITE_STRING("suicide");
			MESSAGE_END();
				
		}
	}
	else
	{
		UTIL_LogPrintf( "\"%s<%i><%s><%s>\" commited suicide with \"%s\" (world)\n",
				STRING( vic->pev->netname ), 
				GETPLAYERUSERID(vic->edict() ), 
				GETPLAYERAUTHID(vic->edict() ),
				TEAM_NAME(vic->pev->team),
				STRING(killer->classname));
		MESSAGE_BEGIN(MSG_ALL,gmsgDeath);
			WRITE_BYTE(0);
			WRITE_BYTE(vic->entindex());
			WRITE_STRING(STRING(killer->classname));
		MESSAGE_END();
		
	}
	if(!m_bPrestart)
		vic->m_iDeaths++;

	MESSAGE_BEGIN( MSG_SPEC, SVC_DIRECTOR );
		WRITE_BYTE ( 9 );
		WRITE_BYTE (DRC_CMD_EVENT );	// player killed
		WRITE_SHORT(ENTINDEX(vic->edict()));	// index number of primary entity
		WRITE_SHORT(ENTINDEX(ENT(killer)));	// index number of secondary entity
		WRITE_LONG( 7 | DRC_FLAG_DRAMATIC);   // eventflags (priority and flags)
	MESSAGE_END();
	
	MESSAGE_BEGIN( MSG_ALL, gmsgScoreInfo);
		WRITE_BYTE(ENTINDEX(vic->edict()));
		WRITE_SHORT(vic->pev->frags);
		WRITE_SHORT(vic->m_iDeaths);
		WRITE_SHORT(0);
		WRITE_SHORT(vic->pev->team);
	MESSAGE_END();
	if(!m_bPrestart) {
		edict_t *e;
		int numred=0,numblue=0;
		for(int i=1;i<=gpGlobals->maxClients;i++)
		{
			e=INDEXENT(i);
			if((!e)||e->free)
				continue;
			if(e->v.team==TEAM_BLUE && !e->v.deadflag)
				numblue++;
			else if(e->v.team==TEAM_RED && !e->v.deadflag)
				numred++;
		}
		if(!numred&&!numblue)
			EndRound(WIN_DRAW);
		else if(!numred)
			EndRound(WIN_BLUE);
		else if(!numblue)
			EndRound(WIN_RED);
	}
}

void restart_round() 
{
	if(gRules->m_RoundState==ROUND_ACTIVE) 
	{
		gRules->m_flRoundTime=gpGlobals->time+1.0f;
		UTIL_ClientPrintAll(HUD_PRINTCENTER,"Round Restarting");
		gRules->m_iBlueScore=gRules->m_iRedScore=0;
		MESSAGE_BEGIN(MSG_ALL,gmsgTeamScore,NULL);
			WRITE_BYTE(gRules->m_iRedScore);
			WRITE_BYTE(gRules->m_iBlueScore);
		MESSAGE_END();
		for ( int i = 1; i <= gpGlobals->maxClients; i++ )
		{
			CBasePlayer *plr = (CBasePlayer *)UTIL_PlayerByIndex( i );
			if ( plr )
			{
				plr->pev->frags=0;
				plr->m_iDeaths=0;
				MESSAGE_BEGIN( MSG_ALL, gmsgScoreInfo);
					WRITE_BYTE( i );
					WRITE_SHORT( plr->pev->frags );
					WRITE_SHORT( plr->m_iDeaths );
					WRITE_SHORT( 0 );
					WRITE_SHORT(plr->pev->team);
				MESSAGE_END();
			}
		}
	}
}



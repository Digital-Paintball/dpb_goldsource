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
#include "eiface.h"
#include "util.h"
#include "game.h"

cvar_t	displaysoundlist = {"displaysoundlist","0"};

// multiplayer server rules

// multiplayer server rules
cvar_t	mp_friendlyfire= {"mp_friendlyfire","0", FCVAR_SERVER };
cvar_t	decalfrequency = {"decalfrequency","30", FCVAR_SERVER };
cvar_t  mp_chattime = {"mp_chattime","5", FCVAR_SERVER };
cvar_t	mp_timelimit	= {"mp_timelimit","20", FCVAR_SERVER };
cvar_t  mp_roundlimit  = {"mp_roundlimit","15",FCVAR_SERVER };
cvar_t  mp_freezetime  = {"mp_freezetime","5",FCVAR_SERVER };
cvar_t	mp_roundtime	= {"mp_roundtime","180", FCVAR_SERVER };
cvar_t	mp_returnflag	= {"mp_returnflag","0",FCVAR_SERVER};
cvar_t	mp_respawntime	= {"mp_respawntime","-1",FCVAR_SERVER};
cvar_t	mp_changeteams	= {"mp_changeteams","0",FCVAR_SERVER};
cvar_t	mp_startcredits	= {"mp_startcredits","100",FCVAR_SERVER};
cvar_t	mp_maxcredits	= {"mp_maxcredits","100",FCVAR_SERVER};
cvar_t	mp_roundcredits	= {"mp_roundcredits","0",FCVAR_SERVER};
cvar_t	mp_markcredits	= {"mp_markcredits","0",FCVAR_SERVER};
cvar_t	mp_warmuptime	= {"mp_warmuptime","30",FCVAR_SERVER};
// Engine Cvars
cvar_t 	*g_psv_gravity = NULL;
cvar_t	*g_psv_aim = NULL;
cvar_t	*g_footsteps = NULL;


// Register your console variables here
// This gets called one time when the game is initialied
extern void restart_round();
void GameDLLInit( void )
{
	// Register cvars here:

	g_psv_gravity = CVAR_GET_POINTER( "sv_gravity" );
	g_psv_aim = CVAR_GET_POINTER( "sv_aim" );
	g_footsteps = CVAR_GET_POINTER( "mp_footsteps" );

	CVAR_REGISTER (&displaysoundlist);
	CVAR_REGISTER (&mp_friendlyfire);
	CVAR_REGISTER (&decalfrequency);
	CVAR_REGISTER (&mp_chattime);
	CVAR_REGISTER (&mp_timelimit);
	CVAR_REGISTER (&mp_roundlimit);
	CVAR_REGISTER (&mp_freezetime);
	CVAR_REGISTER (&mp_roundtime);
	CVAR_REGISTER (&mp_changeteams);
	CVAR_REGISTER (&mp_returnflag);
	CVAR_REGISTER (&mp_respawntime);
	CVAR_REGISTER (&mp_startcredits);
	CVAR_REGISTER (&mp_maxcredits);
	CVAR_REGISTER (&mp_roundcredits);
	CVAR_REGISTER (&mp_markcredits);
	CVAR_REGISTER (&mp_warmuptime);
	g_engfuncs.pfnAddServerCommand("restartround",&restart_round);
}


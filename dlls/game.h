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

#ifndef GAME_H
#define GAME_H

extern void GameDLLInit( void );


extern cvar_t	displaysoundlist;

// multiplayer server rules
extern cvar_t	mp_timelimit;
extern cvar_t	mp_friendlyfire;
extern cvar_t	decalfrequency;
extern cvar_t	mp_chattime;
extern cvar_t	mp_roundtime;
extern cvar_t	mp_returnflag;
extern cvar_t	mp_respawntime;
extern cvar_t	mp_changeteams;
extern cvar_t	mp_roundlimit;
extern cvar_t	mp_freezetime;
extern cvar_t	mp_startcredits;
extern cvar_t	mp_maxcredits;
extern cvar_t	mp_roundcredits;
extern cvar_t	mp_markcredits;
extern cvar_t	mp_warmuptime;

// Engine Cvars
extern cvar_t	*g_psv_gravity;
extern cvar_t	*g_psv_aim;
extern cvar_t	*g_footsteps;

#endif		// GAME_H
 

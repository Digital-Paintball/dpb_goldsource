#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"cweapon.h"
#include"hud.h"
extern local_state_s *g_finalstate;
extern int	g_runfuncs;
extern float g_lastFOV;

CA5 a5;
CBlazer blazer;
COmen omen;
CDM4 dm4;
CAngel angel;
CExcal excal;
CSpyder spyder;
CSL68 sl68;
CMag mag;
CCocker cocker;
CBush bush;
CM98 m98;
CPhantom phantom;
CShocker shocker;
CEmag emag;
COrracle orracle;
CTimmy timmy;
CImpulse impulse;
CMatrix matrix;
ClientWeapon *weapons[WEAPON_MAX];
static int g_currentanim;


/*
=====================
HUD_SendWeaponAnim

Change weapon model animation
=====================
*/
void HUD_SendWeaponAnim( int iAnim, int body, int force );


int HUD_GetWeaponAnim( void );
void initballs();
void HUD_InitWeapons( void )
{
	static int initialized = 0;
	if ( initialized )
		return;
	initialized = 1;

	for(int i=0;i<WEAPON_MAX;i++)
		weapons[i]=0;
	weapons[WEAPON_ANGEL]=&angel;
	weapons[WEAPON_EXCAL]=&excal;
	weapons[WEAPON_SPYDER]=&spyder;
	weapons[WEAPON_SL68]=&sl68;
	weapons[WEAPON_MAG]=&mag;
	weapons[WEAPON_COCKER]=&cocker;
	weapons[WEAPON_BUSH]=&bush;
	weapons[WEAPON_M98]=&m98;
	weapons[WEAPON_PHANTOM]=&phantom;
	weapons[WEAPON_SHOCKER]=&shocker;
	weapons[WEAPON_EMAG]=&emag;
	weapons[WEAPON_ORRACLE]=&orracle;
	weapons[WEAPON_TIMMY]=&timmy;
	weapons[WEAPON_IMPULSE]=&impulse;
	weapons[WEAPON_MATRIX]=&matrix;
	weapons[WEAPON_A5]=&a5;
	weapons[WEAPON_BLAZER]=&blazer;
	weapons[WEAPON_OMEN]=&omen;
	weapons[WEAPON_DM4]=&dm4;
	// Allocate slot(s) for each weapon that we are going to be predicting
}
extern int g_iIntermission;
void HUD_WeaponsFrame(double time)
{
	HUD_InitWeapons();
	int i;
	if(gHUD.m_Hopper.m_iCurWeapon!=-1&&weapons[gHUD.m_Hopper.m_iCurWeapon]&&!g_iIntermission)
		weapons[gHUD.m_Hopper.m_iCurWeapon]->Frame(time);
}


void HUD_WeaponsThink( local_state_s *from, local_state_s *to, usercmd_t *cmd, double time, unsigned int random_seed )
{
#if 0
/*	int i;
	static int lasthealth;

//	memset( &nulldata, 0, sizeof( nulldata ) );

	HUD_InitWeapons();	

	// Get current clock
//	gpGlobals->time = time;
	// Fill in data based on selected weapon
	// FIXME, make this a method in each weapon?  where you pass in an entity_state_t *?
/*	switch ( from->client.m_iId )
	{		
	
	
	}*/
	// Store pointer to our destination entity_state_t so we can get our origin, etc. from it
	//  for setting up events on the client
	g_finalstate = to;

	// If we are running events/etc. go ahead and see if we
	//  managed to die between last frame and this one
	// If so, run the appropriate player killed or spawn function
//	gEngfuncs.Con_Printf("FROM H: %f\nTO H: %f\n",from->client.health,to->client.health);
	pl.m_iCurWeapon=from->client.m_iId;
	if(from->client.m_iId==-1)
	{
		pl.havegun=0;
		return;
	}

	for ( i = 0; i < 32; i++ )
	{
		if ( !weapons[i] )
			continue;
		weapons[i]->m_iHopper			= from->weapondata[i].m_iClip;
	//	gEngfuncs.Con_Printf("HOPPER: %i\n",weapons[i]->m_iHopper);
	//	weapons[i]->m_flPrimaryAttack	= from->weapondata[i].m_flNextPrimaryAttack;
	//	weapons[i]->m_flSecondaryAttack = from->weapondata[i].m_flNextSecondaryAttack;
	//	weapons[i]->m_flIdle			= from->weapondata[i].m_flTimeWeaponIdle;
//		weapons[i]->m_bReload			= from->weapondata[i].m_fInReload;
//		weapons[i]->m_flReload			= from->weapondata[i].m_fReloadTime;
//		weapons[i]->m_flPump			= from->weapondata[i].m_flPumpTime;
	//	weapons[i]->m_bPrimaryAttack	= from->weapondata[i].iuser1;
	//	weapons[i]->m_bSecondaryAttack	= from->weapondata[i].iuser2;

	}
	pl.random = random_seed;

	// Get old buttons from previous state.
/*	pl.oldbuttons = from->playerstate.oldbuttons;*

	// Which buttsons chave changed
	buttonsChanged = (player.m_afButtonLast ^ cmd->buttons);	// These buttons have changed this frame
	
	// Debounced button codes for pressed/released
	// The changed ones still down are "pressed"
	player.m_afButtonPressed =  buttonsChanged & cmd->buttons;	
	// The ones not down are "released"
	player.m_afButtonReleased = buttonsChanged & (~cmd->buttons);
*/
	// Set player variables that weapons code might check/alter
	pl.buttons = cmd->buttons;

/*	player.pev->velocity = from->client.velocity;
	player.pev->flags = from->client.flags;

	player.pev->deadflag = from->client.deadflag;
	player.pev->waterlevel = from->client.waterlevel;
	player.pev->maxspeed    = from->client.maxspeed;*/
	pl.fov = from->client.fov;
	pl.weaponanim = from->client.weaponanim;
	pl.viewmodel = from->client.viewmodel;
	pl.m_iTube=from->client.ammo_nails;
	pl.m_iFullTubes=from->client.ammo_shells;
	
/*	player.m_iHopper=(int)from->client.ammo_nails;
	gHUD.m_Hopper.pctHopper=(float)player.m_iHopper/200.0f;
		
	player.m_flNextAttack = from->client.m_flNextAttack;
	player.m_flNextAmmoBurn = from->client.fuser2;
	player.m_flAmmoStartCharge = from->client.fuser3;
*/
	//Stores all our ammo info, so the client side weapons can use them.
	// Point to current weapon object
	if(weapons[from->client.m_iId])
		pl.havegun=1;
	else
		pl.havegun=0;
	
	// Assume that we are not going to switch weapons
	to->client.m_iId					= from->client.m_iId;

	// Now see if we issued a changeweapon command ( and we're not dead )
/*	if ( cmd->weaponselect && ( player.pev->deadflag != ( DEAD_DISCARDBODY + 1 ) ) )
	{
		// Switched to a different weapon?
		if ( from->weapondata[ cmd->weaponselect ].m_iId == cmd->weaponselect )
		{
			CBasePlayerWeapon *pNew = g_pWpns[ cmd->weaponselect ];
			if ( pNew && ( pNew != pWeapon ) )
			{
				// Put away old weapon
				if (player.m_pActiveItem)
					player.m_pActiveItem->Holster( );
				
				player.m_pLastItem = player.m_pActiveItem;
				player.m_pActiveItem = pNew;

				// Deploy new weapon
				if (player.m_pActiveItem)
				{
					player.m_pActiveItem->Deploy( );
				}

				// Update weapon id so we can predict things correctly.
				to->client.m_iId = cmd->weaponselect;
			}
		}
	}*/

	// Copy in results of prediction code
	to->client.viewmodel				= pl.viewmodel;
	to->client.fov						= pl.fov;
	to->client.weaponanim				= pl.weaponanim;
/*	to->client.fuser2					= player.m_flNextAmmoBurn;
	to->client.fuser3					= player.m_flAmmoStartCharge;
	to->client.maxspeed					= player.pev->maxspeed;*/

	//HL Weapons
/*	to->client.vuser1[0]				= player.ammo_9mm;
	to->client.vuser1[1]				= player.ammo_357;
	to->client.vuser1[2]				= player.ammo_argrens;

	to->client.ammo_nails				= player.ammo_bolts;
	to->client.ammo_shells				= player.ammo_buckshot;
	to->client.ammo_cells				= player.ammo_uranium;
	to->client.vuser2[0]				= player.ammo_hornets;
	to->client.ammo_rockets				= player.ammo_rockets;

	if ( player.m_pActiveItem->m_iId == WEAPON_RPG )
	{
		 from->client.vuser2[ 1 ] = ( ( CRpg * )player.m_pActiveItem)->m_fSpotActive;
		 from->client.vuser2[ 2 ] = ( ( CRpg * )player.m_pActiveItem)->m_cActiveRockets;
	}
*/
	// Make sure that weapon animation matches what the game .dll is telling us
	//  over the wire ( fixes some animation glitches )
/*	if ( g_runfuncs && ( HUD_GetWeaponAnim() != to->client.weaponanim ) )
	{
		int body = 2;

		
		
		// Force a fixed anim down to viewmodel
		HUD_SendWeaponAnim( to->client.weaponanim, body, 1 );
	}*/
	for ( i = 0; i < 32; i++ )
	{
		if ( !weapons[i] )
			continue;
		from->weapondata[i].m_iId=i;
		from->weapondata[i].m_iClip	=weapons[i]->m_iHopper;
		from->weapondata[i].m_flNextPrimaryAttack=weapons[i]->m_flPrimaryAttack; 
		from->weapondata[i].m_flNextSecondaryAttack=weapons[i]->m_flSecondaryAttack ;
		from->weapondata[i].m_flTimeWeaponIdle=weapons[i]->m_flIdle;
		from->weapondata[i].m_fInReload=weapons[i]->m_iReload;
		from->weapondata[i].m_fReloadTime=weapons[i]->m_flReload;
//		from->weapondata[i].m_flPumpTime=weapons[i]->m_flPump;
		from->weapondata[i].iuser1=weapons[i]->m_bPrimaryAttack;
		from->weapondata[i].iuser2=weapons[i]->m_bSecondaryAttack;
		to->weapondata[i].m_flNextPrimaryAttack		-= cmd->msec / 1000.0;
		to->weapondata[i].m_flNextSecondaryAttack	-= cmd->msec / 1000.0;
		to->weapondata[i].m_flTimeWeaponIdle		-= cmd->msec / 1000.0;
		
		if ( to->weapondata[i].m_flNextPrimaryAttack < -1.0 )
			to->weapondata[i].m_flNextPrimaryAttack = -1.0;
		if ( to->weapondata[i].m_flNextSecondaryAttack < -0.001 )
			to->weapondata[i].m_flNextSecondaryAttack = -0.001;
		if ( to->weapondata[i].m_flTimeWeaponIdle < -0.001 )
			to->weapondata[i].m_flTimeWeaponIdle = -0.001;
	}


	// m_flNextAttack is now part of the weapons, but is part of the player instead
	to->client.m_flNextAttack -= cmd->msec / 1000.0;
	if ( to->client.m_flNextAttack < -0.001 )
		to->client.m_flNextAttack = -0.001;
	// Store off the last position from the predicted state.

	// Wipe it so we can't use it after this frame
	g_finalstate = NULL;

#endif
}

int g_Random;
int g_Buttons;
extern "C" void __declspec(dllexport) HUD_PostRunCmd( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed )
{
	g_runfuncs = runfuncs;
	g_Random = random_seed/5;
	g_Buttons = cmd->buttons;
	static double lasttime=0;
/*	if(runfuncs) {
		HUD_WeaponsFrame(time-lasttime);
		lasttime=time;
	}*/
//	HUD_WeaponsThink( from, to, cmd, time, random_seed );
	g_lastFOV = to->client.fov;
}



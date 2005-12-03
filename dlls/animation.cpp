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
#include "util.h"
typedef float vec_hacked;
typedef float vec3_hacked[3];
typedef float vec4_hacked[4];
#ifdef vec_t
#undef vec_t
#endif
#ifdef vec3_t
#undef vec3_t
#endif
#ifdef vec4_t
#undef vec4_t
#endif

#define vec_t vec_hacked
#define vec3_t vec3_hacked
#define vec4_t vec4_hacked
// hack into header files that we can ship
typedef int qboolean;
typedef unsigned char byte;
#include "cbase.h"
#include "studio.h"
#ifndef ACTIVITY_H
#include "activity.h"
#endif

#include "activitymap.h"

#ifndef ANIMATION_H
#include "animation.h"
#endif

#ifndef SCRIPTEVENT_H
#include "scriptevent.h"
#endif

#ifndef ENGINECALLBACK_H
#include "enginecallback.h"
#endif
#include "com_model.h"
#include"r_studioint.h"
#include "studio_util.h"

int VectorCompare(float *,float *);
extern globalvars_t				*gpGlobals;

void SV_StudioSetupBones(struct model_s *pMode, float frame, int sequence, const float angles[3], const float origin[3], const byte *pcontroller, const byte *pblending, int iBone, const edict_t *pEdict);

sv_blending_interface_t svBlending = 
{
	SV_BLENDING_INTERFACE_VERSION,
	&SV_StudioSetupBones
};

server_studio_api_t IEngineStudio;

studiohdr_t *g_pstudiohdr;
float (*g_pRotationMatrix)[3][4];
float (*g_pBoneTransform)[MAXSTUDIOBONES][3][4];

extern "C" int REAL_EXPORT Server_GetBlendingInterface(int version, struct sv_blending_interface_s **ppinterface, struct engine_studio_api_s *pstudio, float (*rotationmatrix)[3][4],float (*bonetransform)[MAXSTUDIOBONES][3][4])

{
	if(version!=SV_BLENDING_INTERFACE_VERSION )
		return 0;
	
	*ppinterface=&svBlending;
	memcpy(&IEngineStudio,pstudio,sizeof(IEngineStudio));
	g_pRotationMatrix = rotationmatrix;
	g_pBoneTransform = bonetransform;
	return 1;
}

mstudioanim_t *StudioGetAnim(model_t *psubmodel,mstudioseqdesc_t *pseqdesc) 
{
	mstudioseqgroup_t *pseqgroup;
	cache_user_t *paSequences;

	pseqgroup = (mstudioseqgroup_t*)((byte*)g_pstudiohdr+g_pstudiohdr->seqgroupindex)+pseqdesc->seqgroup;
	if(!pseqdesc->seqgroup)
		return (mstudioanim_t*)((byte*)g_pstudiohdr+pseqgroup->data+pseqdesc->animindex);
	paSequences=(cache_user_t*)psubmodel->submodels;
	if(!paSequences) {
		paSequences=(cache_user_t*)IEngineStudio.Mem_Calloc(16,sizeof(cache_user_t));
		psubmodel->submodels=(dmodel_t*)paSequences;
	}
	if(!IEngineStudio.Cache_Check((struct cache_user_s*)&(paSequences[pseqdesc->seqgroup])))
	{
		ALERT(at_console,"loading %s\n",pseqgroup->name);
		IEngineStudio.LoadCacheFile(pseqgroup->name,(struct cache_user_s*)&paSequences[pseqdesc->seqgroup]);
	}
	return (mstudioanim_t*)((byte*)paSequences[pseqdesc->seqgroup].data+pseqdesc->animindex);
}


void StudioCalcBoneAdj(float dadt, float *adj, const byte *pcontroller) 
{
	int i,j;
	float val;
	mstudiobonecontroller_t *pbonecontroller =
		(mstudiobonecontroller_t*)((byte*)g_pstudiohdr + g_pstudiohdr->bonecontrollerindex);
	for(j=0;j<g_pstudiohdr->numbonecontrollers;j++) {
		i=pbonecontroller[j].index;
		if(i<=3) {
			if(pbonecontroller[j].type&STUDIO_RLOOP)
			{
				val=(pcontroller[i]*dadt)*(360.0f/256.0)+pbonecontroller[j].start;
			} else {
				val=(pcontroller[i]*dadt)/255.0;
				if(val<0) val=0;
				else if(val>1) val=1;
				val=(1.0-val)*pbonecontroller[j].start+val*pbonecontroller[j].end;
			}
			switch(pbonecontroller[j].type&STUDIO_TYPES) {
			case STUDIO_XR:	
			case STUDIO_YR:
			case STUDIO_ZR:
				adj[j]=val*(M_PI/180.0);
				break;
			case STUDIO_X:	
			case STUDIO_Y:
			case STUDIO_Z:
				adj[j]=val;
				break;
			}
			
		}
	}
}
void StudioCalcBonePosition(int frame,float s,mstudiobone_t *pbone,mstudioanim_t *panim,float *adj,float *pos)
{
	int j,k;
	mstudioanimvalue_t *panimvalue;
	
	for(j=0;j<3;j++) {
		pos[j]=pbone->value[j];
		if(panim->offset[j]!=0) {
			panimvalue=(mstudioanimvalue_t*)((byte*)panim+panim->offset[j]);
			k=frame;
			if(panimvalue->num.total < panimvalue->num.valid)
				k=0;
			while(panimvalue->num.total <= k) {
				k-=panimvalue->num.total;
				panimvalue+=panimvalue->num.valid+1;
				if(panimvalue->num.total < panimvalue->num.valid)
					k=0;
			}
			if(panimvalue->num.valid>k) {
				if(panimvalue->num.valid>k+1)
					pos[j]+=(panimvalue[k+1].value*(1.0-s)+s*panimvalue[k+2].value)*pbone->scale[j];
				else 
					pos[j]+=panimvalue[k+1].value*pbone->scale[j];
			} else {
				if(panimvalue->num.total <= k+1) 
					pos[j]+=(panimvalue[panimvalue->num.valid].value*(1.0-s)+s*panimvalue[panimvalue->num.valid+2].value)*pbone->scale[j];
				else
					pos[j]+=panimvalue[panimvalue->num.valid].value*pbone->scale[j];
			}
		}
		if(pbone->bonecontroller[j]!=-1)
			pos[j]+=adj[pbone->bonecontroller[j]];		
	}
}
void StudioCalcBoneQuaternion(int frame,float s,mstudiobone_t *pbone,mstudioanim_t *panim,float *adj,float *q,int ibone,const edict_t *ent,float pitch)
{
	int j,k;
	float q1[4],q2[4];
	float angle1[3],angle2[3];
	mstudioanimvalue_t *panimvalue;
	for(j=0;j<3;j++) {
		if(panim->offset[j+3]==0)
			angle1[j]=angle2[j]=pbone->value[j+3];
		else {
			panimvalue=(mstudioanimvalue_t*)((byte*)panim+panim->offset[j+3]);
			k=frame;
			if(panimvalue->num.total < panimvalue->num.valid)
				k=0;
			while(panimvalue->num.total <= k) {
				k-=panimvalue->num.total;
				panimvalue+=panimvalue->num.valid+1;
				if(panimvalue->num.total < panimvalue->num.valid)
					k=0;
			}
			if(panimvalue->num.valid>k) {
				angle1[j]=panimvalue[k+1].value;
				if(panimvalue->num.valid>k+1)
					angle2[j]=panimvalue[k+2].value;
				else {
					if(panimvalue->num.total > k + 1)
 						angle2[j]=angle1[j];
					else
						angle2[j]=panimvalue[panimvalue->num.valid+2].value;
				}
			} else {
				angle1[j]=panimvalue[panimvalue->num.valid].value;
				if(panimvalue->num.total > k+1) 
					angle2[j]=angle1[j];
				else
					angle2[j]=panimvalue[panimvalue->num.valid+1].value;
			}
			angle1[j]=pbone->value[j+3]+angle1[j]*pbone->scale[j+3];
			angle2[j]=pbone->value[j+3]+angle2[j]*pbone->scale[j+3];
		}
		if(pbone->bonecontroller[j+3]!=-1)
		{
			angle1[j]+=adj[pbone->bonecontroller[j+3]];
			angle2[j]+=adj[pbone->bonecontroller[j+3]];
		}
	}
	if(ibone>0&&ibone<5) {
		float da;
		da=(pitch/4.0) * (M_PI/180.0);
		angle1[2]+=da;
		angle2[2]+=da;
	}
	if(!VectorCompare(angle1,angle2))
	{
		AngleQuaternion(angle1,q1);
		AngleQuaternion(angle2,q2);
		QuaternionSlerp(q1,q2,s,q);
	} else
		AngleQuaternion(angle1,q);
}
void StudioCalcRotations(float pos[][3],float q[][4],mstudioseqdesc_t *pseqdesc,mstudioanim_t *panim,const byte *pcontroller,float f,const edict_t *ent,float pitch)
{
	int i;
	int frame;
	mstudiobone_t *pbone;
	float s;
	float adj[MAXSTUDIOCONTROLLERS];
	if(f>pseqdesc->numframes-1)
		f=0;
	else if(f < -0.01)
		f=-0.01;

	frame=(int)f;
	s=(f-frame);
	pbone=(mstudiobone_t*)((byte*)g_pstudiohdr+g_pstudiohdr->boneindex);
	StudioCalcBoneAdj(1.0,adj,pcontroller);
	for(i=0;i<g_pstudiohdr->numbones;i++,pbone++,panim++)
	{
		StudioCalcBoneQuaternion(frame,s,pbone,panim,adj,q[i],i,ent,pitch);
		StudioCalcBonePosition(frame,s,pbone,panim,adj,pos[i]);
	}
	if(pseqdesc->motiontype&STUDIO_X)
		pos[pseqdesc->motionbone][0]=0.0;
	if(pseqdesc->motiontype&STUDIO_Y)
		pos[pseqdesc->motionbone][1]=0.0;
	if(pseqdesc->motiontype&STUDIO_Z)
		pos[pseqdesc->motionbone][2]=0.0;
}
	
void SV_StudioSetupBones(struct model_s *pModel, float frame,int sequence, const float angles[3], const float origin[3], const byte *pcontroller, const byte *pblending, int iBone, const edict_t *pEdict)
{
	int i;
	mstudiobone_t	*pbones;
	mstudioseqdesc_t *pseqdesc;
	mstudioanim_t *panim;
	float ang[3];
	static float pos[MAXSTUDIOBONES][3];
	static float	q[MAXSTUDIOBONES][4];
	float		bonematrix[3][4];
	ang[2]=0;
	ang[1]=angles[1];
	ang[0]=0;
	g_pstudiohdr=(studiohdr_t*)IEngineStudio.Mod_Extradata(pModel);
	if(sequence<0||sequence>=g_pstudiohdr->numseq)
		sequence=0;
	AngleMatrix(ang,(*g_pRotationMatrix));
	(*g_pRotationMatrix)[0][3]=origin[0];	
	(*g_pRotationMatrix)[1][3]=origin[1];	
	(*g_pRotationMatrix)[2][3]=origin[2];	
	ang[0]=angles[0]*3.0;
	if(ang[0]<-60.0)
		ang[0]=-60.0;
	else if(ang[0]>60.0)
		ang[0]=60.0;
	pseqdesc=(mstudioseqdesc_t*)((byte*)g_pstudiohdr+g_pstudiohdr->seqindex)+ sequence;

	panim=StudioGetAnim(pModel,pseqdesc);
	StudioCalcRotations(pos,q,pseqdesc,panim,pcontroller,frame,pEdict,ang[0]);
	pbones=(mstudiobone_t*)((byte*)g_pstudiohdr+g_pstudiohdr->boneindex);
	
	for(i=0;i<g_pstudiohdr->numbones;i++)
	{
		QuaternionMatrix(q[i],bonematrix);
		bonematrix[0][3]=pos[i][0];
		bonematrix[1][3]=pos[i][1];
		bonematrix[2][3]=pos[i][2];

		if(pbones[i].parent == -1) 
			ConcatTransforms((*g_pRotationMatrix),bonematrix,(*g_pBoneTransform)[i]);
		else
			ConcatTransforms((*g_pBoneTransform)[pbones[i].parent],bonematrix,(*g_pBoneTransform)[i]);
	}
}



int ExtractBbox( void *pmodel, int sequence, float *mins, float *maxs )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return 0;

	mstudioseqdesc_t	*pseqdesc;

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);
	
	mins[0] = pseqdesc[ sequence ].bbmin[0];
	mins[1] = pseqdesc[ sequence ].bbmin[1];
	mins[2] = pseqdesc[ sequence ].bbmin[2];

	maxs[0] = pseqdesc[ sequence ].bbmax[0];
	maxs[1] = pseqdesc[ sequence ].bbmax[1];
	maxs[2] = pseqdesc[ sequence ].bbmax[2];

	return 1;
}


int LookupActivity( void *pmodel, entvars_t *pev, int activity )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return 0;

	mstudioseqdesc_t	*pseqdesc;

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);

	int weighttotal = 0;
	int seq = ACTIVITY_NOT_AVAILABLE;
	for (int i = 0; i < pstudiohdr->numseq; i++)
	{
		if (pseqdesc[i].activity == activity)
		{
			weighttotal += pseqdesc[i].actweight;
			if (!weighttotal || RANDOM_LONG(0,weighttotal-1) < pseqdesc[i].actweight)
				seq = i;
		}
	}

	return seq;
}


int LookupActivityHeaviest( void *pmodel, entvars_t *pev, int activity )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if ( !pstudiohdr )
		return 0;

	mstudioseqdesc_t	*pseqdesc;

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);

	int weight = 0;
	int seq = ACTIVITY_NOT_AVAILABLE;
	for (int i = 0; i < pstudiohdr->numseq; i++)
	{
		if (pseqdesc[i].activity == activity)
		{
			if ( pseqdesc[i].actweight > weight )
			{
				weight = pseqdesc[i].actweight;
				seq = i;
			}
		}
	}

	return seq;
}

void GetEyePosition ( void *pmodel, float *vecEyePosition )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;

	if ( !pstudiohdr )
	{
		ALERT ( at_console, "GetEyePosition() Can't get pstudiohdr ptr!\n" );
		return;
	}

	pstudiohdr->eyeposition[0]=vecEyePosition[0];
	pstudiohdr->eyeposition[1]=vecEyePosition[1];
	pstudiohdr->eyeposition[2]=vecEyePosition[2];
}

int LookupSequence( void *pmodel, const char *label )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return 0;

	mstudioseqdesc_t	*pseqdesc;

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);

	for (int i = 0; i < pstudiohdr->numseq; i++)
	{
		if (stricmp( pseqdesc[i].label, label ) == 0)
			return i;
	}

	return -1;
}


int IsSoundEvent( int eventNumber )
{
	if ( eventNumber == SCRIPT_EVENT_SOUND || eventNumber == SCRIPT_EVENT_SOUND_VOICE )
		return 1;
	return 0;
}


void SequencePrecache( void *pmodel, const char *pSequenceName )
{
	int index = LookupSequence( pmodel, pSequenceName );
	if ( index >= 0 )
	{
		studiohdr_t *pstudiohdr;
	
		pstudiohdr = (studiohdr_t *)pmodel;
		if ( !pstudiohdr || index >= pstudiohdr->numseq )
			return;

		mstudioseqdesc_t	*pseqdesc;
		mstudioevent_t		*pevent;

		pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + index;
		pevent = (mstudioevent_t *)((byte *)pstudiohdr + pseqdesc->eventindex);

		for (int i = 0; i < pseqdesc->numevents; i++)
		{
			// Don't send client-side events to the server AI
			if ( pevent[i].event >= EVENT_CLIENT )
				continue;

			// UNDONE: Add a callback to check to see if a sound is precached yet and don't allocate a copy
			// of it's name if it is.
			if ( IsSoundEvent( pevent[i].event ) )
			{
				if ( !strlen(pevent[i].options) )
				{
					ALERT( at_error, "Bad sound event %d in sequence %s :: %s (sound is \"%s\")\n", pevent[i].event, pstudiohdr->name, pSequenceName, pevent[i].options );
				}

				PRECACHE_SOUND( (char *)(gpGlobals->pStringBase + ALLOC_STRING(pevent[i].options) ) );
			}
		}
	}
}



void GetSequenceInfo( void *pmodel, entvars_t *pev, float *pflFrameRate, float *pflGroundSpeed )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return;

	mstudioseqdesc_t	*pseqdesc;

	if (pev->sequence >= pstudiohdr->numseq)
	{
		*pflFrameRate = 0.0;
		*pflGroundSpeed = 0.0;
		return;
	}

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + (int)pev->sequence;

	if (pseqdesc->numframes > 1)
	{
		*pflFrameRate = 256 * pseqdesc->fps / (pseqdesc->numframes - 1);
		*pflGroundSpeed = sqrt( pseqdesc->linearmovement[0]*pseqdesc->linearmovement[0]+ pseqdesc->linearmovement[1]*pseqdesc->linearmovement[1]+ pseqdesc->linearmovement[2]*pseqdesc->linearmovement[2] );
		*pflGroundSpeed = *pflGroundSpeed * pseqdesc->fps / (pseqdesc->numframes - 1);
	}
	else
	{
		*pflFrameRate = 256.0;
		*pflGroundSpeed = 0.0;
	}
}


int GetSequenceFlags( void *pmodel, entvars_t *pev )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if ( !pstudiohdr || pev->sequence >= pstudiohdr->numseq )
		return 0;

	mstudioseqdesc_t	*pseqdesc;
	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + (int)pev->sequence;

	return pseqdesc->flags;
}


int GetAnimationEvent( void *pmodel, entvars_t *pev, MonsterEvent_t *pMonsterEvent, float flStart, float flEnd, int index )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if ( !pstudiohdr || pev->sequence >= pstudiohdr->numseq || !pMonsterEvent )
		return 0;

	mstudioseqdesc_t	*pseqdesc;
	mstudioevent_t		*pevent;

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + (int)pev->sequence;
	pevent = (mstudioevent_t *)((byte *)pstudiohdr + pseqdesc->eventindex);

	if (pseqdesc->numevents == 0 || index > pseqdesc->numevents )
		return 0;

	if (pseqdesc->numframes > 1)
	{
		flStart *= (pseqdesc->numframes - 1) / 256.0;
		flEnd *= (pseqdesc->numframes - 1) / 256.0;
	}
	else
	{
		flStart = 0;
		flEnd = 1.0;
	}

	for (; index < pseqdesc->numevents; index++)
	{
		// Don't send client-side events to the server AI
		if ( pevent[index].event >= EVENT_CLIENT )
			continue;

		if ( (pevent[index].frame >= flStart && pevent[index].frame < flEnd) || 
			((pseqdesc->flags & STUDIO_LOOPING) && flEnd >= pseqdesc->numframes - 1 && pevent[index].frame < flEnd - pseqdesc->numframes + 1) )
		{
			pMonsterEvent->event = pevent[index].event;
			pMonsterEvent->options = pevent[index].options;
			return index + 1;
		}
	}
	return 0;
}

float SetController( void *pmodel, entvars_t *pev, int iController, float flValue )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return flValue;

	mstudiobonecontroller_t	*pbonecontroller = (mstudiobonecontroller_t *)((byte *)pstudiohdr + pstudiohdr->bonecontrollerindex);

	// find first controller that matches the index
	int i;
	for ( i = 0; i < pstudiohdr->numbonecontrollers; i++, pbonecontroller++)
	{
		if (pbonecontroller->index == iController)
			break;
	}
	if (i >= pstudiohdr->numbonecontrollers)
		return flValue;

	// wrap 0..360 if it's a rotational controller

	if (pbonecontroller->type & (STUDIO_XR | STUDIO_YR | STUDIO_ZR))
	{
		// ugly hack, invert value if end < start
		if (pbonecontroller->end < pbonecontroller->start)
			flValue = -flValue;

		// does the controller not wrap?
		if (pbonecontroller->start + 359.0 >= pbonecontroller->end)
		{
			if (flValue > ((pbonecontroller->start + pbonecontroller->end) / 2.0) + 180)
				flValue = flValue - 360;
			if (flValue < ((pbonecontroller->start + pbonecontroller->end) / 2.0) - 180)
				flValue = flValue + 360;
		}
		else
		{
			if (flValue > 360)
				flValue = flValue - (int)(flValue / 360.0) * 360.0;
			else if (flValue < 0)
				flValue = flValue + (int)((flValue / -360.0) + 1) * 360.0;
		}
	}

	int setting = (int) (255 * (flValue - pbonecontroller->start) / (pbonecontroller->end - pbonecontroller->start));

	if (setting < 0) setting = 0;
	if (setting > 255) setting = 255;
	pev->controller[iController] = setting;

	return setting * (1.0 / 255.0) * (pbonecontroller->end - pbonecontroller->start) + pbonecontroller->start;
}


float SetBlending( void *pmodel, entvars_t *pev, int iBlender, float flValue )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return flValue;

	mstudioseqdesc_t	*pseqdesc;

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + (int)pev->sequence;

	if (pseqdesc->blendtype[iBlender] == 0)
		return flValue;

	if (pseqdesc->blendtype[iBlender] & (STUDIO_XR | STUDIO_YR | STUDIO_ZR))
	{
		// ugly hack, invert value if end < start
		if (pseqdesc->blendend[iBlender] < pseqdesc->blendstart[iBlender])
			flValue = -flValue;

		// does the controller not wrap?
		if (pseqdesc->blendstart[iBlender] + 359.0 >= pseqdesc->blendend[iBlender])
		{
			if (flValue > ((pseqdesc->blendstart[iBlender] + pseqdesc->blendend[iBlender]) / 2.0) + 180)
				flValue = flValue - 360;
			if (flValue < ((pseqdesc->blendstart[iBlender] + pseqdesc->blendend[iBlender]) / 2.0) - 180)
				flValue = flValue + 360;
		}
	}

	int setting = (int) (255 * (flValue - pseqdesc->blendstart[iBlender]) / (pseqdesc->blendend[iBlender] - pseqdesc->blendstart[iBlender]));

	if (setting < 0) setting = 0;
	if (setting > 255) setting = 255;

	pev->blending[iBlender] = setting;

	return setting * (1.0 / 255.0) * (pseqdesc->blendend[iBlender] - pseqdesc->blendstart[iBlender]) + pseqdesc->blendstart[iBlender];
}




int FindTransition( void *pmodel, int iEndingAnim, int iGoalAnim, int *piDir )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return iGoalAnim;

	mstudioseqdesc_t	*pseqdesc;
	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);

	// bail if we're going to or from a node 0
	if (pseqdesc[iEndingAnim].entrynode == 0 || pseqdesc[iGoalAnim].entrynode == 0)
	{
		return iGoalAnim;
	}

	int	iEndNode;

	// ALERT( at_console, "from %d to %d: ", pEndNode->iEndNode, pGoalNode->iStartNode );

	if (*piDir > 0)
	{
		iEndNode = pseqdesc[iEndingAnim].exitnode;
	}
	else
	{
		iEndNode = pseqdesc[iEndingAnim].entrynode;
	}

	if (iEndNode == pseqdesc[iGoalAnim].entrynode)
	{
		*piDir = 1;
		return iGoalAnim;
	}

	byte *pTransition = ((byte *)pstudiohdr + pstudiohdr->transitionindex);

	int iInternNode = pTransition[(iEndNode-1)*pstudiohdr->numtransitions + (pseqdesc[iGoalAnim].entrynode-1)];

	if (iInternNode == 0)
		return iGoalAnim;

	int i;

	// look for someone going
	for (i = 0; i < pstudiohdr->numseq; i++)
	{
		if (pseqdesc[i].entrynode == iEndNode && pseqdesc[i].exitnode == iInternNode)
		{
			*piDir = 1;
			return i;
		}
		if (pseqdesc[i].nodeflags)
		{
			if (pseqdesc[i].exitnode == iEndNode && pseqdesc[i].entrynode == iInternNode)
			{
				*piDir = -1;
				return i;
			}
		}
	}

	ALERT( at_console, "error in transition graph" );
	return iGoalAnim;
}

void SetBodygroup( void *pmodel, entvars_t *pev, int iGroup, int iValue )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return;

	if (iGroup > pstudiohdr->numbodyparts)
		return;

	mstudiobodyparts_t *pbodypart = (mstudiobodyparts_t *)((byte *)pstudiohdr + pstudiohdr->bodypartindex) + iGroup;

	if (iValue >= pbodypart->nummodels)
		return;

	int iCurrent = (pev->body / pbodypart->base) % pbodypart->nummodels;

	pev->body = (pev->body - (iCurrent * pbodypart->base) + (iValue * pbodypart->base));
}


int GetBodygroup( void *pmodel, entvars_t *pev, int iGroup )
{
	studiohdr_t *pstudiohdr;
	
	pstudiohdr = (studiohdr_t *)pmodel;
	if (! pstudiohdr)
		return 0;

	if (iGroup > pstudiohdr->numbodyparts)
		return 0;

	mstudiobodyparts_t *pbodypart = (mstudiobodyparts_t *)((byte *)pstudiohdr + pstudiohdr->bodypartindex) + iGroup;

	if (pbodypart->nummodels <= 1)
		return 0;

	int iCurrent = (pev->body / pbodypart->base) % pbodypart->nummodels;

	return iCurrent;
}

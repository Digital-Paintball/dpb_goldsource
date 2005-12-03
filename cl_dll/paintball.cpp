#include"extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "cl_util.h"
#include "util.h"
#include "entity_state.h"
#include "usercmd.h"
#include"pm_defs.h"
#include"cweapon.h"
#include "r_efx.h"
#include"hud.h"
#include"studio.h"
#include"r_studioint.h"
#include"triangleapi.h"
extern "C" int PM_ClipVelocity (float *in, float* normal, float *out, float overbounce);
extern engine_studio_api_t IEngineStudio;
#define DRAG_COEFF (0.000763) // kuja 2.2:  .0012
class pbnode
{
public:
		float origin[3];
		float velocity[3];
		int bounce;
		pbnode *next;
		float threshold;
};

pbnode *pbroot[32];
int pbcolor[32];
pbnode *addball(int slot) 
{
		pbnode *ball=new pbnode;
		if(!ball) {
				gEngfuncs.Con_DPrintf("WARNING: Could not alloc memory for paintball!");
				return NULL;
		}
		ball->next=pbroot[slot];
		pbroot[slot]=ball;
		return ball;
}

void delnextball(pbnode *ball,int slot)
{
		pbnode *temp;
		if(!ball) {
				temp=pbroot[slot];
				pbroot[slot]=temp->next;
				delete temp;
		} else {
				temp=ball->next;
				ball->next=temp->next;
				delete temp;
		}
}

void RemoveBalls()
{
	int i;
	pbnode *cur,*temp;
	for(i=0;i<32;i++) {
		for(cur=pbroot[i];cur;) {
			temp=cur;
			cur=cur->next;
			delete temp;
		}
		pbroot[i]=NULL;
	}
}
void PaintballHit(pmtrace_t *tr)
{
	char fname[]="weapons/pbhit0.wav";
	char splat[9];
	fname[13]=(char)gEngfuncs.pfnRandomLong(1,9)+'0';
	sprintf(splat,"{splat%i",gEngfuncs.pfnRandomLong(0,17));
	static int i=0;

	physent_t *pe;
	pe = gEngfuncs.pEventAPI->EV_GetPhysent( tr->ent );
	if (   pe && ( pe->solid == SOLID_BSP || pe->movetype == MOVETYPE_PUSHSTEP ) )
	{
		if ( gEngfuncs.pfnGetCvarFloat ( "r_decals" ) )
		{
			gEngfuncs.pEfxAPI->R_DecalShoot( 
				gEngfuncs.pEfxAPI->Draw_DecalIndex( gEngfuncs.pEfxAPI->Draw_DecalIndexFromName( splat ) ), 
				gEngfuncs.pEventAPI->EV_IndexFromTrace( tr ), 0, tr->endpos, 0 );
		}
	}
	vec3_t test;
	VectorSubtract(tr->endpos,v_origin,test);
	gEngfuncs.pEventAPI->EV_PlaySound( 0, tr->endpos, CHAN_STATIC, fname, gEngfuncs.pfnRandomFloat(0.92, 1.0), ATTN_NORM, 0, 96 + gEngfuncs.pfnRandomLong(0,0xf) );
}
extern float	g_BonePositions[32][ MAXSTUDIOBONES ][ 3 ][ 4 ];
void RealTrace(vec3_t start, vec3_t end,pmtrace_t *tr,int ignore) 
{
	vec3_t dir,c[2],vec[3],o;
	int idx,i,x;
	cl_entity_t *ent;
	studiohdr_t *hdr;
	mstudiobbox_t *bbox;
	float t_near,t_far,t_max,t,vd,vn;
	gEngfuncs.pEventAPI->EV_PlayerTrace(start,end,PM_NORMAL,ignore,tr);
	if(tr->fraction==1.0f)
		return;
	idx=gEngfuncs.pEventAPI->EV_IndexFromTrace(tr);
	if(idx<1 || idx > gEngfuncs.GetMaxClients()) 
		return;
	ent=gEngfuncs.GetEntityByIndex(idx);
	if(!ent)
		return;
	hdr=(studiohdr_t*)IEngineStudio.Mod_Extradata(ent->model);
	bbox=(mstudiobbox_t*)((unsigned long)hdr + hdr->hitboxindex);
	idx--;
	VectorSubtract(end,start,dir);
	VectorScale(dir,1/Length(dir),dir);
	for(i=hdr->numhitboxes-1;i>=0;i--,bbox++) {
		vec[0][0]=g_BonePositions[idx][bbox->bone][0][0];
		vec[0][1]=g_BonePositions[idx][bbox->bone][1][0];
		vec[0][2]=g_BonePositions[idx][bbox->bone][2][0];
		vec[1][0]=g_BonePositions[idx][bbox->bone][0][1];
		vec[1][1]=g_BonePositions[idx][bbox->bone][1][1];
		vec[1][2]=g_BonePositions[idx][bbox->bone][2][1];
		vec[2][0]=g_BonePositions[idx][bbox->bone][0][2];
		vec[2][1]=g_BonePositions[idx][bbox->bone][1][2];
		vec[2][2]=g_BonePositions[idx][bbox->bone][2][2];
		o[0]=g_BonePositions[idx][bbox->bone][0][3];
		o[1]=g_BonePositions[idx][bbox->bone][1][3];
		o[2]=g_BonePositions[idx][bbox->bone][2][3];
		VectorMA(o,bbox->bbmax[0],vec[0],c[0]);
		VectorMA(c[0],bbox->bbmax[1],vec[1],c[0]);
		VectorMA(c[0],bbox->bbmax[2],vec[2],c[0]);
		VectorMA(o,bbox->bbmin[0],vec[0],c[1]);
		VectorMA(c[1],bbox->bbmin[1],vec[1],c[1]);
		VectorMA(c[1],bbox->bbmin[2],vec[2],c[1]);
		t_near=-99999.0;
		t_far=99999.0;
		t_max=99999.0f;
		for(x=0;x<2;x++) {
			if(x)  {
				VectorInverse(vec[0]);
				VectorInverse(vec[1]);
				VectorInverse(vec[2]);
			}
			for(int j=0;j<3;j++) {
				vd=DotProduct(dir,vec[j]);
				if(vd==0.0f)
					continue;
				vn=DotProduct(vec[j],start)-DotProduct(vec[j],c[x]);
				t=-vn/vd;
				if(vd>0.0&&t<t_far)
					t_far=t;
				else if(vd<0.0f&&t>t_near)
					t_near=t;
				if(t_near>t_far)
					goto box_end;
			}
		}
		tr->fraction=0.5f;
		return;
box_end:
		do { } while(0);
	}
	tr->fraction=1.0f;
}
void RunPaintballs(float time)
{
	pbnode *prev,*cur;
	float neworigin[3],speed;
	static float whiztime=0;
	pmtrace_t tr;
	int i;
	cl_entity_s *me=gEngfuncs.GetLocalPlayer();
	whiztime-=time;
	gEngfuncs.pEventAPI->EV_SetUpPlayerPrediction( false, true );
	for(i=gEngfuncs.GetMaxClients()-1;i>=0;i--) {
		gEngfuncs.pEventAPI->EV_PushPMStates();
		gEngfuncs.pEventAPI->EV_SetSolidPlayers (i);	
		gEngfuncs.pEventAPI->EV_SetTraceHull(2);
		for(prev=NULL,cur=pbroot[i];cur;prev=cur,cur=cur->next) {
			VectorMA(cur->origin,time,cur->velocity,neworigin);
			RealTrace(cur->origin,neworigin,&tr,i+1);
			if(tr.fraction!=1.0f) {
				if(!cur->bounce) {
					if(Length(cur->velocity)>cur->threshold)
						PaintballHit(&tr);
					else {
						cur->bounce=1;
						PM_ClipVelocity(cur->velocity,tr.plane.normal,cur->velocity,2.0);
						VectorScale(cur->velocity,0.15,cur->velocity);
						VectorCopy(tr.endpos,cur->origin);
						continue;
					}	
				}
				delnextball(prev,i);
				if(prev)
					cur=prev;
				else
					cur=pbroot[i];
				if(cur)
					continue;
				break;
			}
			VectorCopy(neworigin,cur->origin);
			speed=Length(cur->velocity);
			if(i!=me->index-1&&speed>125.0*12.0) {
				VectorSubtract(neworigin,v_origin,neworigin);
				if(Length(neworigin)<72.0) {
			    		whiztime=0.15;
					gEngfuncs.pEventAPI->EV_PlaySound( i+1, cur->origin, CHAN_ITEM, "weapons/whiz.wav", gEngfuncs.pfnRandomFloat(0.92, 1.0), ATTN_NORM, 0, 98 + gEngfuncs.pfnRandomLong( 0, 3) );		
				}
			}		
			cur->velocity[2]-=284.0f*time; // kuja original value, 384.0f (32 feet per second, normal gravity)
			VectorScale(cur->velocity,1.0/(1.0+DRAG_COEFF*time*speed),cur->velocity);
		}
		gEngfuncs.pEventAPI->EV_PopPMStates();
	}
}

void FirePaintball(float *origin,float *velocity,int owner,int color)
{
	pbnode *pb=addball(owner-1);
	if(pb) {
		pbcolor[owner-1]=color;
		VectorScale(velocity,280.0*12.0,pb->velocity);
		VectorCopy(origin,pb->origin);
		pb->bounce=0;
		pb->threshold=gEngfuncs.pfnRandomFloat(50.0f,100.0f)*12.0f;
	}
}
#define PB_SCALE 0.85

float paintcolors[7][3] =  { 
	{ 1.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 0.5, 0.0 },
	{ 0.9, 0.9, 0.9 },
	{ 1.0, 0.5, 1.0 },
	{ 0.0, 0.0, 1.0 }
};
/*
void DrawPaintballs() 
{
	int i;
	pbnode *cur;
	gEngfuncs.pTriAPI->SpriteTexture((struct model_s*)gEngfuncs.GetSpritePointer(gHUD.m_Hopper.pb), 0 );
	gEngfuncs.pTriAPI->RenderMode( kRenderNormal);
	gEngfuncs.pTriAPI->CullFace( TRI_FRONT );
	for(i=gEngfuncs.GetMaxClients()-1;i>=0;i--) {
		gEngfuncs.pTriAPI->Color4f(paintcolors[pbcolor[i]][0],paintcolors[pbcolor[i]][1],paintcolors[pbcolor[i]][2],1.0);
		for(cur=pbroot[i];cur;cur=cur->next) {

			gEngfuncs.pTriAPI->Begin(TRI_TRIANGLE_STRIP);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0],cur->origin[1],cur->origin[2]-0.7*PB_SCALE);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0]-0.7*PB_SCALE,cur->origin[1]+0.7*PB_SCALE,cur->origin[2]);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0]-0.7*PB_SCALE,cur->origin[1]-0.7*PB_SCALE,cur->origin[2]);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0],cur->origin[1],cur->origin[2]+0.7*PB_SCALE);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0]+PB_SCALE,cur->origin[1],cur->origin[2]);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0]-0.7*PB_SCALE,cur->origin[1]+0.7*PB_SCALE,cur->origin[2]);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0],cur->origin[1],cur->origin[2]-0.7*PB_SCALE);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0]-0.7*PB_SCALE,cur->origin[1]-0.7*PB_SCALE,cur->origin[2]);
			gEngfuncs.pTriAPI->Vertex3f(cur->origin[0]+PB_SCALE,cur->origin[1],cur->origin[2]);
			gEngfuncs.pTriAPI->End();
		}
	}
}
*/
void VectorAngles( const float *forward, float *angles );
void DrawPaintballs() 
{
	int i;
	pbnode *cur;
	float ang[3],r[3],u[3];
	gEngfuncs.pTriAPI->SpriteTexture((struct model_s*)gEngfuncs.GetSpritePointer(gHUD.m_Hopper.pb), 0 );
	gEngfuncs.pTriAPI->RenderMode( kRenderNormal);
	gEngfuncs.pTriAPI->CullFace( TRI_NONE );
	for(i=gEngfuncs.GetMaxClients()-1;i>=0;i--) {
		gEngfuncs.pTriAPI->Color4f(paintcolors[pbcolor[i]][0],paintcolors[pbcolor[i]][1],paintcolors[pbcolor[i]][2],1.0);
		for(cur=pbroot[i];cur;cur=cur->next) {
			VectorSubtract(cur->origin,v_origin,r);
			VectorAngles(r,ang);
			ang[0]=-ang[0];
			AngleVectors(ang,NULL,r,u);
		
			gEngfuncs.pTriAPI->Begin(TRI_TRIANGLE_STRIP);
			VectorMA(cur->origin,PB_SCALE,u,ang);
			VectorMA(ang,-PB_SCALE,r,ang);
			gEngfuncs.pTriAPI->TexCoord2f(0.0f,0.0f);
			gEngfuncs.pTriAPI->Vertex3fv(ang);


			VectorMA(cur->origin,-PB_SCALE,u,ang);
			VectorMA(ang,-PB_SCALE,r,ang);
			gEngfuncs.pTriAPI->TexCoord2f(0.0f,1.0f);
			gEngfuncs.pTriAPI->Vertex3fv(ang);

			VectorMA(cur->origin,PB_SCALE,u,ang);
			VectorMA(ang,PB_SCALE,r,ang);
			gEngfuncs.pTriAPI->TexCoord2f(1.0f,0.0f);
			gEngfuncs.pTriAPI->Vertex3fv(ang);

			VectorMA(cur->origin,-PB_SCALE,u,ang);
			VectorMA(ang,PB_SCALE,r,ang);
			gEngfuncs.pTriAPI->TexCoord2f(1.0f,1.0f);
			gEngfuncs.pTriAPI->Vertex3fv(ang);
			gEngfuncs.pTriAPI->End();
		}
	}
}

#include"extdll.h"
#include"util.h"
#include"player.h"
#include"rules.h"
#define DRAG_COEFF (0.000763) // reduced as in client.
extern "C" int PM_ClipVelocity(float *in,float *normal,float *out,float overbounce);
unsigned short g_usPaintball;
class pbnode
{
public:
		float origin[3];
		float velocity[3];
		float threshold;
		pbnode *next;
};

static float Length(const float *v)
{
    int     i;
    float   length;

    length = 0;
    for (i=0 ; i< 3 ; i++)
        length += v[i]*v[i];
    length = sqrt (length);     // FIXME

    return length;
}

static void VectorScale (const float *in, float scale, float *out)
{
    out[0] = in[0]*scale;
    out[1] = in[1]*scale;
    out[2] = in[2]*scale;
}

static void VectorMA (const float *veca, float scale, const float *vecb, float *vecc)
{
    vecc[0] = veca[0] + scale*vecb[0];
    vecc[1] = veca[1] + scale*vecb[1];
    vecc[2] = veca[2] + scale*vecb[2];
}
static void VectorCopy (const float *in, float *out)
{
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
}
pbnode *pbroot[32];
pbnode *addball(int slot) 
{
		pbnode *ball=new pbnode;
		if(!ball) {
				ALERT(at_console,"WARNING: Could not alloc memory for paintball!");
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
void RemoveBalls(int owner) {
	if(!owner) {
		for(int i=1;i<=gpGlobals->maxClients;i++)
			RemoveBalls(i);
	} else {
		pbnode *cur,*temp;
		for(cur=pbroot[owner-1];cur;) {
			temp=cur;
			cur=cur->next;
			delete temp;
		}
		pbroot[owner-1]=NULL;
	}
}

void RunPaintballs()
{
	pbnode *prev,*cur;
	float neworigin[3];
	TraceResult tr;
	int i;
	edict_t *e;
	for(i=0;i<gpGlobals->maxClients;i++) {
		e=INDEXENT(i+1);
		if((!e)||e->free)
			continue;
		for(prev=NULL,cur=pbroot[i];cur;prev=cur,cur=cur->next) {
			VectorMA(cur->origin,gpGlobals->frametime,cur->velocity,neworigin);
			TRACE_LINE(cur->origin,neworigin,0,e,&tr);
			if(tr.flFraction!=1.0f) {
				if(tr.pHit&&Length(cur->velocity)>cur->threshold) {
						int idx=ENTINDEX(tr.pHit);
						if(idx>0&&idx<=gpGlobals->maxClients&&gRules.CanTakeDamage(tr.pHit,e)) {
							CBasePlayer *plr=(CBasePlayer*)CBaseEntity::Instance(tr.pHit);
							if(plr) {
								plr->pev->health=0;
								plr->Killed(&(e->v),0);
							}
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
			cur->velocity[2]-=284.0f*gpGlobals->frametime; // kuja reduced as in client
			VectorScale(cur->velocity,1.0/(1.0+DRAG_COEFF*gpGlobals->frametime*Length(cur->velocity)),cur->velocity);
		}
	}
}

void FirePaintball(float *origin,float *velocity,int owner)
{
	pbnode *pb=addball(owner-1);
	if(pb) {
		VectorScale(velocity,280.0*12.0,pb->velocity);
		VectorCopy(origin,pb->origin);
		pb->threshold=RANDOM_FLOAT(50.0f,100.0f)*12.0;
	}
}



void CPod::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev),"models/droppod.mdl");
	pev->movetype=MOVETYPE_TOSS;
	pev->solid=SOLID_TRIGGER;
	pev->takedamage=DAMAGE_NO;
	SetThink(NULL);
	SetTouch(&CPod::Touch);
	pev->gravity=0.5;
	pev->avelocity[0]=RANDOM_FLOAT(100,300);
	pev->avelocity[1]=RANDOM_FLOAT(100,300);
	pev->avelocity[2]=RANDOM_FLOAT(100,300);
}

void CPod::Precache()
{
	PRECACHE_MODEL("models/droppod.mdl");
}

void CPod::Touch(CBaseEntity *pOther)
{
	if(pOther->IsPlayer())
		return;
	SetTouch(NULL);
	UTIL_Remove(this);
}
LINK_ENTITY_TO_CLASS(pod,CPod);

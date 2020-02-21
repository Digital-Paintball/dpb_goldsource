#include"extdll.h"
#include"util.h"
#include"player.h"
#include"rules.h"
#define DRAG_COEFF (0.000763) // reduced as in client.

extern "C" int PM_ClipVelocity(float *in,float *normal,float *out,float overbounce);
unsigned short g_usPaintball;

#include "paintballs.h"
PaintBallManager gBallManager;

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


void PaintBallManager::RemoveBalls(int idx)
{
	if (idx == -1) {
		for (int i = 0; i < balls.size(); i++) {
			delete balls[i];
		}
		balls.clear();
	}
	else {
		int size = balls.size();
		std::vector<pBall_t*> copy = balls;
		balls.clear();
		for (int i = 0; i < copy.size(); i++) {
			if (copy[i]->playerIndex == idx) {
				delete copy[i];
			}
			else {
				balls.push_back(copy[i]);
			}
		}
	}
}

void PaintBallManager::RemoveBall(pBall_t* ball) {
	balls.erase(
		std::remove_if(
			balls.begin(),
			balls.end(),
			[ball](pBall_t * pb) { return pb = ball; }
		),
		balls.end()
	);
	delete ball;
}


void PaintBallManager::FirePaintball(float *origin, float *velocity, int owner)
{
	pBall_t* newBall = new pBall_t;
	newBall->playerIndex = owner;
	VectorScale(velocity, 280.0*12.0, newBall->velocity);
	VectorCopy(origin, newBall->origin);
	newBall->threshold = RANDOM_FLOAT(50.0f, 100.0f) * 12.0;
	balls.push_back(newBall); //add the new ball to the list for processorizing
}

void PaintBallManager::RunPaintballs()
{
	std::vector<pBall_t*>::iterator iter;
	std::vector<pBall_t*> cleanup;

	float neworigin[3];
	TraceResult tr;

	edict_t *e;
	for (iter = balls.begin(); iter != balls.end(); ++iter)
	{
		pBall_t* pb = *iter;
		e = INDEXENT(pb->playerIndex);
		if (!e) {
			cleanup.push_back(pb);
			continue;
		}

		VectorMA(pb->origin, gpGlobals->frametime, pb->velocity, neworigin);
		TRACE_LINE(pb->origin, neworigin, 0, e, &tr);
		if (tr.flFraction < 1.0f )
		{
			if (tr.pHit && Length(pb->velocity) > pb->threshold)
			{
				int idx = ENTINDEX(tr.pHit);
				if (idx > 0 && idx < gpGlobals->maxClients && gRules->CanTakeDamage(tr.pHit,e))
				{
					CBasePlayer *plr = (CBasePlayer*)CBaseEntity::Instance(tr.pHit);
					if (plr)
					{
						plr->pev->health = 0;
						plr->Killed(&(e->v), 0 );
					}
				}
				cleanup.push_back(*iter);
				continue;
			}
		}
		VectorCopy(neworigin, pb->origin);
		pb->velocity[2] -= 284.0f * gpGlobals->frametime; // kuja reduced as in client
		VectorScale(pb->velocity, 1.0/(1.0+DRAG_COEFF * gpGlobals->frametime * Length(pb->velocity)), pb->velocity);
	}

	for (iter = cleanup.begin(); iter != cleanup.end(); ++iter) {
		RemoveBall(*iter);
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

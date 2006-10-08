#ifndef PAINTBALL_H
#define PAINTBALL_H

#include <list>

//Tony; alright, old paintball code is below #ifdef'd out. (har. no it's not!)
//New struct for paintball; we're only going to have _one_ list!!
//each ball has playerIndex, to remove em all (however.. i think they're gonna remove automatically anyway..)
typedef struct pBall_s
{
	float origin[3];
	float velocity[3];
	float threshold;
	int playerIndex;
} pBall_t;

class PaintBallManager
{
public:
	PaintBallManager()
	{
	}
	void FirePaintball(float *origin, float *velocity, int owner);
	void RunPaintballs();
	void RemoveBalls(int idx);
private:
	std::list<pBall_t> paintballs;

};

extern PaintBallManager gBallManager;
#endif
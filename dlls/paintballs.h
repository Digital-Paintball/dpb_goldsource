#ifndef PAINTBALL_H
#define PAINTBALL_H

#include <vector>
#include <algorithm>

// Previous comment mentioned an #if'd code
// Paintball tracks who owns it with playerIndex
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
	void FirePaintball(float *origin, float *velocity, int owner);
	void RunPaintballs();
	void RemoveBalls(int idx);
	void RemoveBall(pBall_t* ball);
private:
	std::vector <pBall_t*> balls;
};

extern PaintBallManager gBallManager;
#endif
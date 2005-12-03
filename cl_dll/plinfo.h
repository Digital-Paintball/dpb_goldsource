#ifndef PLINFO_H

#define PLINFO_H



class plinfo
{
public:
	//void Killed();
	//void Spawn();
	plinfo() { buttons=oldbuttons=lean=0;}
	unsigned int random;
	int buttons;
	int oldbuttons;
	int lean;
	int leandone;
	float leantime;
	float frametime;
};
extern plinfo pl;



void DPB_Seed(unsigned int seed);
float DPB_RandomFloat(float low, float high );

#endif
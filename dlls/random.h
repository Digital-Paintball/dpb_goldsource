#ifndef RANDOM_H
#define RANDOM_H

class RC4
{
public:
	void key  (unsigned char *key, int len);
	void crypt(unsigned char *plaintext, int len);

	unsigned int s[256];
	int i;
	int j;
};
extern RC4 rc4;
void DPB_Seed(unsigned int seed);
float DPB_RandomFloat(float low, float high );
#endif 

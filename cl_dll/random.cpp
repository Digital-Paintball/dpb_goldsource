#include "extdll.h"
#include"wrect.h"
#include"cl_dll.h"
#include "util.h"
#include"cl_entity.h"
#include"random.h"
RC4 rc4;
void RC4::key(unsigned char *key, int len)
{
	int t;
	
	for(i = 0; i < 256; i++) s[i] = i;

	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + s[i] + key[i % len]) % 256;
		t = s[i];
		s[i] = s[j];
		s[j] = t;
	}
	i = j = 0;
}



void RC4::crypt(unsigned char *plaintext, int len)
{
	int t;
	int c;

	c = 0;	
	while(c < len)
	{
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		t = s[i];
		s[i] = s[j];
		s[j] = t;

		t = (s[i] + s[j]) % 256;

		plaintext[c] ^= s[t];
		c++;
	}
}

float DPB_RandomFloat(float low, float high )
{

	unsigned int range;

	range = (unsigned int)(high - low);
	if ( !range )
	{
		return low;
	}
	else
	{
		int t=gEngfuncs.GetLocalPlayer()->index;
		int tensixrand=(t<<24)+(t<<16)+(t<<8)+t;
		float offset;
		rc4.crypt((unsigned char*)&tensixrand,4);
		tensixrand &= 65535;

		offset = (float)(tensixrand / 65536.0);

		return (low + offset * range );
	}
}

void DPB_Seed(unsigned int seed)
{
	unsigned int s=(seed<<16)+seed;
	rc4.key((unsigned char*)&s,4);
}
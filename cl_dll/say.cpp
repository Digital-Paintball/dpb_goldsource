#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "string.h"
#include "wrect.h"

#define MAX_LINES 16
#define MAX_CHARS 512
#define MAX_LINE_WIDTH (ScreenWidth-40)
#define LINE_HEIGHT 13
#define LINE_X 10
#define LINE_Y (YRES(240)-lines/2*LINE_HEIGHT)

char say_text[MAX_LINES][MAX_CHARS];

float say_colors[16][3] = {
	{ 0.8f, 0.8f, 0.8f }, //0
	{ 1.0f, 0.25, 0.25 }, //1
	{ 0.6f, 0.8f, 1.0f }, //2
	{ 0.0f, 1.0f, 0.0f }, //3
	{ 0.0f, 0.0f, 1.0f }, //4
	{ 0.0f, 1.0f, 1.0f }, //5
	{ 0.0f, 1.0f, 1.0f }, //6
	{ 0.0f, 1.0f, 1.0f }, //7
	{ 0.0f, 1.0f, 1.0f }, //8
	{ 0.0f, 1.0f, 1.0f }, //9
	{ 0.0f, 1.0f, 1.0f }, //10
	{ 0.0f, 1.0f, 1.0f }, //11
	{ 0.0f, 1.0f, 1.0f }, //12
	{ 0.0f, 1.0f, 1.0f }, //13
	{ 0.0f, 1.0f, 1.0f }, //14
	{ 0.0f, 1.0f, 1.0f }  //15
};
cvar_t *hud_saytext_lines;
cvar_t *hud_saytext;
cvar_t *hud_saytext_pos;
static inline int num_lines() {
	if(hud_saytext_lines->value<=2)
		return 2;
	if(hud_saytext_lines->value>=MAX_LINES)
		return MAX_LINES;
	return (int)hud_saytext_lines->value;
}
DECLARE_MESSAGE(m_SayText,SayText);
int CHudSayText::Init() {
	HOOK_MESSAGE(SayText);
	hud_saytext=CVAR_CREATE("hud_saytext","1",FCVAR_ARCHIVE);
	hud_saytext_lines=CVAR_CREATE("hud_saytext_lines","6",FCVAR_ARCHIVE);
	hud_saytext_pos=CVAR_CREATE("hud_saytext_pos","180",FCVAR_ARCHIVE);
	gHUD.AddHudElem(this);
	m_iFlags |=HUD_INTERMISSION | HUD_ACTIVE;
	InitHUDData();
	return 1;
}
void RemoveBalls();
void CHudSayText::InitHUDData() 
{
	memset(say_text,0,sizeof(say_text));
	scroll_time=0.0f;
	RemoveBalls();
}
int CHudSayText::VidInit() {
	return 1;
}
int CHudSayText::MsgFunc_SayText( const char *pszName, int iSize, void *pbuf ) {
	BEGIN_READ(pbuf,iSize);
	READ_BYTE();
	SayTextPrint(READ_STRING());
	return 1;
}
void CHudSayText::ScrollTextUp(int lines) {
	if(say_text[0][0])
		ConsolePrint(say_text[0]);
	memmove(say_text,say_text+1,sizeof(say_text[0])*(lines-1));
	memset(say_text[lines-1],0,sizeof(say_text[0]));
}
void CHudSayText::SayTextPrint(char *buf) {
	int j,i,lines;
	int w,h,wonly;
	if(!hud_saytext->value) {
		ConsolePrint(buf);
		return;
	}
	lines=num_lines();
	scroll_time=gHUD.m_flTime+5.0f;

	gEngfuncs.pfnDrawConsoleStringLen(buf,&w,&h);
	for(i=0;i<lines;i++)
			if(!say_text[i][0]) break;
	if(i==lines) {
		ScrollTextUp(lines);
		i=lines-1;
	}
again:
	if(LINE_X+w>MAX_LINE_WIDTH)
	{
		for(wonly=1;wonly>=0;wonly--) {
			for(j=strlen(buf)-1;j>=0;j--) {
				if(!wonly || buf[j]==' ') {
					char t=buf[j];
					buf[j]='\0';
					gEngfuncs.pfnDrawConsoleStringLen(buf,&w,&h);
					if(LINE_X+w<=MAX_LINE_WIDTH) {
						strcpy(say_text[i],buf);
						i++;
						if(i==lines) {
							ScrollTextUp(lines);
							i=lines-1;
						}
						buf=buf+j+1;
						gEngfuncs.pfnDrawConsoleStringLen(buf,&w,&h);
						goto again;
					}
					buf[j]=t;
				}
			}
		}
	}
	else if(*buf)
		strcpy(say_text[i],buf);

}

int CHudSayText::Draw(float flTime) {
	int lines=num_lines();
	for(int i=0;i<lines;i++) {
		char *p=say_text[i],t=p[0];
		if(!t)
			break;
		int more=1;
		int w,h;
		int x=LINE_X;
		while(more) {
			int j,l=strlen(p);
			for(j=0;j<l;j++) {
				if((p[j]&0xff)>=0xf0) {
					t=p[j];
					p[j]='\0';
					break;
				}
			}
			gEngfuncs.pfnDrawConsoleString(x,gHUD.m_scrinfo.iHeight-hud_saytext_pos->value+i*LINE_HEIGHT,p);
			gEngfuncs.pfnDrawConsoleStringLen(p,&w,&h);
			x+=w;
			if(j==l)
				more=0;
			else {
				p[j]=t;
				p+=j+1;
				gEngfuncs.pfnDrawSetTextColor(say_colors[t&0xff-0xf0][0],say_colors[t&0xff-0xf0][1],say_colors[t&0xff-0xf0][2]);
			}
	
		}
	}
	if(flTime>scroll_time) {
		ScrollTextUp(lines);
		scroll_time=flTime+5.0f;
	}
	return 1;
}

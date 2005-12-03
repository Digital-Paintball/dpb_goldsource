#ifndef DPB_BUY_H
#define DPB_BUY_H

#define COST_ANGEL		75
#define COST_COCKER		50
#define COST_MAG			50
#define COST_BUSH			60
#define COST_EXCAL		75
#define COST_M98			40
#define COST_PHANTOM	35
#define COST_SL68			30
#define COST_SPYDER		45
#define COST_SHOCKER	65
#define COST_EMAG			70
#define COST_ORRACLE	65
#define COST_TIMMY		80
#define COST_MATRIX		70
#define COST_IMPULSE	60
#define COST_DM4			80
#define COST_A5				55
#define COST_OMEN			55
#define COST_BLAZER		60

#define COST_STOCK			0
#define COST_STEALTH		15
#define COST_BOOMSTICK	25

#define COST_POD			10

#define MAX_PODS	4


#define BARREL_STOCK 			0
#define BARREL_STEALTH 			1
#define BARREL_STICK	 		2
#define BARREL_MAX 			3


#define WEAPON_ANGEL			0
#define ANGEL_ROF	15.6
#define ANGEL_ACC	8.0

#define WEAPON_EXCAL			1
#define EXCAL_ROF	13.7
#define EXCAL_ACC	6.0

#define WEAPON_SPYDER			2
#define SPYDER_ROF	6.5
#define SPYDER_ACC	14.0

#define WEAPON_SL68			3
#define SL68_ROF	1.95
#define SL68_ACC	2.0

#define WEAPON_MAG			4
#define MAG_ROF		9.1
#define MAG_ACC		13.0


#define WEAPON_COCKER			5
#define COCKER_ROF	7.8
#define COCKER_ACC	4.0

#define WEAPON_BUSH			6
#define BUSH_ROF	13.0
#define BUSH_ACC	10.0

#define WEAPON_M98			7
#define M98_ROF		5.2
#define M98_ACC		15.0

#define WEAPON_PHANTOM			8
#define PHANTOM_ROF	2.6
#define PHANTOM_ACC	1.0

#define WEAPON_SHOCKER			9
#define SHOCKER_ROF	10.5
#define SHOCKER_ACC	5.0

#define WEAPON_EMAG			10
#define EMAG_ROF 	11.5
#define EMAG_ACC 	12.0

#define WEAPON_ORRACLE			11
#define ORRACLE_ROF 	13.6
#define ORRACLE_ACC 	3.0

#define WEAPON_TIMMY			12
#define TIMMY_ROF 	18.0
#define TIMMY_ACC 	9.0

#define WEAPON_MATRIX			13
#define MATRIX_ROF	14.3
#define MATRIX_ACC	7.0

#define WEAPON_IMPULSE			14
#define IMPULSE_ROF	11.7
#define IMPULSE_ACC	11.0

#define WEAPON_DM4			15
#define DM4_ROF		16.2
#define DM4_ACC		3.5

#define WEAPON_OMEN			16
#define OMEN_ROF		9.75
#define OMEN_ACC		5.5

#define WEAPON_A5			17
#define A5_ROF		8.45
#define A5_ACC		4.5

#define WEAPON_BLAZER	18
#define BLAZER_ROF	9.75
#define BLAZER_ACC	5.0

#define WEAPON_MAX		19

#define SEMI_DEPLOY 		0 
#define SEMI_SHOOT 		1
#define SEMI_IDLE 		2
#define SEMI_RELOAD_BEGIN 	3
#define SEMI_RELOAD		4
#define SEMI_RELOAD_END		5
#define SEMI_HOLSTER		6
#define COCKER_SHOOT1		7
#define COCKER_SHOOT2		8
#define PUMP_IN			7
#define PUMP_OUT		8

#define JERSEY_MAX 4
#define MASK_MAX	 4
typedef struct weapon_s {
	char *entname;
	int cost;
	char *name;
	char *filename;
} weapon_t;

typedef struct barrel_s {
	int cost;
	char *name;
	char *filename;
	float scale;
} barrel_t;

extern const weapon_t gWeapons[WEAPON_MAX];
extern const barrel_t gBarrels[BARREL_MAX];
#endif


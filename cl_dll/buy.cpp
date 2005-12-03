#include "buy.h"

const weapon_t gWeapons[WEAPON_MAX] = {
	{ "weapon_angel",   COST_ANGEL,   "Angel A4",      "angel"},
	{ "weapon_excal",   COST_EXCAL,   "Excalibur",     "excal"},
	{ "weapon_spyder",  COST_SPYDER,  "Spyder Rodeo",  "spyder"},
	{ "weapon_sl68",    COST_SL68,    "SL68",          "sl68"},
	{ "weapon_mag",     COST_MAG,     "Micromag",      "mag"},
	{ "weapon_cocker",  COST_COCKER,  "Trilogy",       "cocker"},
	{ "weapon_bush",    COST_BUSH,    "Bushmaster",    "bush"},
	{ "weapon_m98",     COST_M98,     "M98 Custom",    "m98"},
	{ "weapon_phantom", COST_PHANTOM, "Phantom",       "phantom"},
	{ "weapon_shocker", COST_SHOCKER, "Shocker 2003",  "shocker"},
	{ "weapon_emag",    COST_EMAG,    "E-Mag",         "emag"},
	{ "weapon_orracle", COST_ORRACLE, "E-Orracle",     "orracle"},
	{ "weapon_timmy",   COST_TIMMY,   "Intimidator",   "timmy"},
	{ "weapon_matrix",  COST_MATRIX,  "E-Matrix",      "matrix"},
	{ "weapon_impulse", COST_IMPULSE, "Impulse",       "impulse"},
	{ "weapon_dm4",     COST_DM4,     "DM5",           "dm4"},
	{ "weapon_omen",    COST_OMEN,    "Evil Omen",     "omen"},
	{ "weapon_a5",      COST_A5,      "Tippmann A5",   "a5"},
	{ "weapon_blazer",  COST_BLAZER,  "Palmer Blazer", "blazer"}
};
const barrel_t gBarrels[BARREL_MAX] = {
	{ COST_STOCK,     "Stock",          "stock",     1.0f},
	{ COST_STEALTH,   "Armson Stealth", "stealth",   0.5f},
	{ COST_BOOMSTICK, "Dye Boomstick",  "boomstick", 0.25f}
};


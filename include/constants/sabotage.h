#pragma once

#include "gba/types.h"

/*
    New type of battle. 
    * At the start of turn, and every three subsquent turns, one random active trap
      and one random passive trap is activated.

    * Passive traps are applied throughout the field and have no activation condition.
      They are announced at the start of their activation turn.

      Examples: Graveyard (All Pokemon gain Ghost-type), Trapper's Territory (All Pokemon
      can't switch out), Bizzare Temple (All Pokemon have a 50% chance to switch moves with
      their opponent)

    * Active traps are hidden to the player and have an activation condition.
      They are only announced when they are activated. They last for 3 turns, except when their
      effect ends, then the next turn a new trap is set.

      Examples: No Interference (Using an item cancels the effect and ends the turn),
      Shattered Dreams (If the trainer attempts to Mega Evolve, use a Z-Move, Dynamax
      or Terastallize, and other gimmicks, the action fails and the turn ends),
      Jackpot! (50% for the trap to pop-up and guarantee a crit)
*/


enum SabotageEffects
{
    SABOTAGE_EFFECT_ON_SWITCHIN,
    SABOTAGE_EFFECT_BATTLE_START
};

#define SABOTAGE_TRAP_NONE 0

// Passive Traps
enum SabotageTraps
{
    // Passive Traps
    SABOTAGE_TRAP_TRAPPERS_TERRITORY, // All Pokémon cannot switch out
    SABOTAGE_TRAP_GRAVEYARD, // All Pokémon gain Ghost-type (can have up to 3 types)
    SABOTAGE_TRAP_WRONG_INTUITION, // Pokémon will use a different move than intended
    SABOTAGE_TRAP_BIZZARE_TEMPLE,  // 50% chance to switch moves with opponent
    SABOTAGE_TRAP_DISTORTED_FURY, // Physical moves become Special and vice-versa

    SABOTAGE_TRAP_PASSIVE_COUNT,

    // Active Traps
    SABOTAGE_TRAP_NO_INTERFERENCE = SABOTAGE_TRAP_PASSIVE_COUNT, // Using an item cancels the effect and ends the turn
    SABOTAGE_TRAP_SHATTERED_DREAMS, // Mega/Z/Dyna/Tera fail and turn ends
    SABOTAGE_TRAP_JACKPOT, // 75% chance to guarantee a critical hit
    SABOTAGE_TRAP_DETONATION_DELUSION, // 33% chance for any move to become Explosion
    SABOTAGE_TRAP_NOTHING_SPECIAL, // Normal-type moves become a random type

    SABOTAGE_TRAP_TOTAL_COUNT = (SABOTAGE_TRAP_NOTHING_SPECIAL + 1)
};

#define SABOTAGE_TRAP_ACTIVE_COUNT (SABOTAGE_TRAP_TOTAL_COUNT - SABOTAGE_TRAP_PASSIVE_COUNT)

// Structure for holding trap data
struct TrapData
{
    u8 *name;
    u8 *desc;
};

extern struct TrapData gTrapData[SABOTAGE_TRAP_TOTAL_COUNT];

// Flavor Text
extern u8 sText_Name_TrappersTerritory[];
extern u8 sText_Name_Graveyard[];
extern u8 sText_Name_WrongIntuition[];
extern u8 sText_Name_BizzareTemple[];
extern u8 sText_Name_DistortedFury[];

extern u8 sText_Name_NoInterference[];
extern u8 sText_Name_ShatteredDreams[];
extern u8 sText_Name_Jackpot[];
extern u8 sText_Name_DetonationDelusion[];
extern u8 sText_Name_NothingSpecial[];


extern u8 sText_Desc_TrappersTerritory[];
extern u8 sText_Desc_Graveyard[];
extern u8 sText_Desc_WrongIntuition[];
extern u8 sText_Desc_BizzareTemple[];
extern u8 sText_Desc_DistortedFury[];

extern u8 sText_Desc_NoInterference[];
extern u8 sText_Desc_ShatteredDreams[];
extern u8 sText_Desc_Jackpot[];
extern u8 sText_Desc_DetonationDelusion[];
extern u8 sText_Desc_NothingSpecial[];

// Flavor Text Tables
extern const u8 *sSabotageTraps_NameTable[SABOTAGE_TRAP_TOTAL_COUNT] = 
{
    sText_Name_TrappersTerritory,
    sText_Name_Graveyard,
    sText_Name_WrongIntuition,
    sText_Name_BizzareTemple,
    sText_Name_DistortedFury,
    sText_Name_NoInterference,
    sText_Name_ShatteredDreams,
    sText_Name_Jackpot,
    sText_Name_DetonationDelusion,
    sText_Name_NothingSpecial
};

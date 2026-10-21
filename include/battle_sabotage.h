#pragma once

#include "constants/sabotage.h"

#define SABOTAGE_TIMER_ACTIVE gBattleStruct->sabotage.activeTrapCtr
#define SABOTAGE_TIMER_PASSIVE gBattleStruct->sabotage.passiveTrapCtr

// Exported Functions
u8 GetRandomTrap(bool8 isActive); // Returns a random trap ID
void SetRandomActiveTrap(void); // Sets a random active trap
void SetRandomPassiveTrap(void); // Sets a random passive trap
const u8* GetTrapName(u8 trapId); // Returns the name of the given trap ID
//const u8* GetTrapDesc(u8 trapId); // Returns the description of the given trap ID
bool8 IsPassiveTrapCounterZero(void); // Returns whether the passive trap counter is zero
bool8 IsActiveTrapCounterZero(void); // Returns whether the active trap counter is zero
void ResetActiveTrapCounter(void); // Resets the active trap counter to 3
void ResetPassiveTrapCounter(void); // Resets the passive trap counter to 3
bool8 IsValidTrapId(u8 trapId); // Returns whether the given trap ID is valid
bool8 IsSabotageBattle(void); // Returns whether the current battle is a Sabotage battle

bool32 SabotageBattleEffects(enum SabotageEffects caseId, u32 battler, enum SabotageTraps trapId); // Applies the effects of the given trap ID
u8 GetCurrentActiveTrap(void); // Returns the current active trap ID
u8 GetCurrentPassiveTrap(void); // Returns the current passive trap ID
void SabotageTrapPopUp(enum SabotageTraps trapId, bool8 isActiveTrap);

#include "global.h"
#include "battle.h"
#include "battle_sabotage.h"
#include "event_data.h"

#include "constants/items.h"
#include "constants/species.h"

u8 GetRandomTrap(bool8 isActive)
{
    // u8 start = isActive ? SABOTAGE_TRAP_PASSIVE_COUNT : SABOTAGE_TRAP_TRAPPERS_TERRITORY;
    // u8 end = isActive ? SABOTAGE_TRAP_TOTAL_COUNT : SABOTAGE_TRAP_PASSIVE_COUNT;

    u8 start = isActive ? SABOTAGE_TRAP_PASSIVE_COUNT : SABOTAGE_TRAP_TRAPPERS_TERRITORY;
    u8 end = isActive ? SABOTAGE_TRAP_TOTAL_COUNT : SABOTAGE_TRAP_WRONG_INTUITION;

    u8 trapId;

    // Prevent getting the same trap twice in a row
    do trapId = start + (Random() % (end - start));
    while (trapId == GetCurrentActiveTrap() || trapId == GetCurrentPassiveTrap());

    return trapId;
}

void SetRandomActiveTrap(void)
{
    gBattleStruct->sabotage.activeTrapId = GetRandomTrap(TRUE);
}

void SetRandomPassiveTrap(void)
{
    gBattleStruct->sabotage.passiveTrapId = GetRandomTrap(FALSE);
}

const u8 *GetTrapName(u8 trapId)
{
    return sSabotageTraps_NameTable[trapId];
}

bool8 IsPassiveTrapCounterZero(void)
{
    return gBattleStruct->sabotage.passiveTrapCtr == 0;
}

bool8 IsActiveTrapCounterZero(void)
{
    return gBattleStruct->sabotage.activeTrapCtr == 0;
}

void ResetActiveTrapCounter(void)
{
    gBattleStruct->sabotage.activeTrapCtr = 3;
}

void ResetPassiveTrapCounter(void)
{
    gBattleStruct->sabotage.passiveTrapCtr = 3;
}

bool8 IsValidTrapId(u8 trapId)
{
    return (trapId > SABOTAGE_TRAP_NONE && trapId < SABOTAGE_TRAP_TOTAL_COUNT);
}

bool8 IsSabotageBattle(void)
{
    return FlagGet(B_FLAG_SABOTAGE_BATTLE);
}

u8 GetCurrentActiveTrap(void)
{
    return gBattleStruct->sabotage.activeTrapId;
}

u8 GetCurrentPassiveTrap(void)
{
    return gBattleStruct->sabotage.passiveTrapId;
}

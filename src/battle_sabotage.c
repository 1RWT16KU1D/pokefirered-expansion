#include "global.h"
#include "battle.h"
#include "battle_sabotage.h"
#include "battle_message.h"
#include "battle_scripts.h"
#include "battle_util.h"
#include "event_data.h"

#include "constants/battle_string_ids.h"
#include "constants/items.h"
#include "constants/species.h"

// Flavor Text Tables
const u8 *const sSabotageTraps_NameTable[SABOTAGE_TRAP_TOTAL_COUNT] =
{
    0,
    sText_Name_TrappersTerritory,
    sText_Name_Graveyard,
    sText_Name_WrongIntuition,
    sText_Name_IntertwinedWill,
    sText_Name_DistortedFury,
    sText_Name_BallroomBonanza,

    sText_Name_BloodPact,
    sText_Name_DetonationDelusion,
    sText_Name_ShatteredDreams,
    sText_Name_Jackpot,
    sText_Name_NothingSpecial,
    sText_Name_PandorasBox,
};

u8 GetRandomTrap(bool8 isActive)
{
    u8 start = isActive ? SABOTAGE_TRAP_BLOOD_PACT : SABOTAGE_TRAP_TRAPPERS_TERRITORY;
    u8 end = isActive ? SABOTAGE_TRAP_SHATTERED_DREAMS + 1 : SABOTAGE_TRAP_INTERTWINED_WILL + 1; // For Debugging

    u8 trapId;

    // Prevent getting the same trap twice in a row
    do trapId = start + (Random() % (end - start));
    while (trapId == GetCurrentActiveTrap() || trapId == GetCurrentPassiveTrap());

    // Debug
    if (isActive)
        return SABOTAGE_TRAP_JACKPOT;

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
    if (!IsValidTrapId(trapId))
        return COMPOUND_STRING("");
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

bool32 TryRunSabotageTrapActivationScript(enum SabotageTraps trapId)
{
    if (trapId < SABOTAGE_TRAP_TRAPPERS_TERRITORY || trapId >= SABOTAGE_TRAP_PASSIVE_COUNT)
        return FALSE;

    gBattleCommunication[MULTISTRING_CHOOSER] = trapId - SABOTAGE_TRAP_TRAPPERS_TERRITORY;
    BattleScriptExecute(BattleScript_SabotageTrapActivation);
    return TRUE;
}

bool32 TryRunShatteredDreamsScript(enum BattlerId battler)
{
    if (!IsSabotageBattle() || GetCurrentActiveTrap() != SABOTAGE_TRAP_SHATTERED_DREAMS)
        return FALSE;

    gBattlerAttacker = gBattleScripting.battler = battler;
    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SHATTERED_DREAMS_ACTIVATES;
    BattleScriptExecute(BattleScript_SabotageTrapActionBlocked);
    gBattleStruct->sabotage.activeTrapConditionMet = TRUE;
    return TRUE;
}

u8 GetCurrentActiveTrap(void)
{
    return gBattleStruct->sabotage.activeTrapId;
}

u8 GetCurrentPassiveTrap(void)
{
    return gBattleStruct->sabotage.passiveTrapId;
}

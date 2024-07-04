# pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum MarkerType         // objectives that can show up on sensors, typically can have slightly inaccurate measurings on sensors 
{
    RACER_MARKER = 0,
    ENVIRONMENT_HAZARD_MARKER = 1,
    BUFF_MARKER = 2,
	GOAL_MARKER = 3,
	EMPTY_MARKER = 4,
};

UENUM(BlueprintType)
enum EntityType         // EXPERIMENTAL, proximity sensor?
{
	EMPTY = 0,
    RACER = 1,
	WANTED_RACER = 2,
	FRIENDLY_NPC = 3,
	NPC_FACTION0 = 4,   // includes mercenaries
    NPC_FACTION1 = 5,
    NPC_FACTION2 = 6,
};

UENUM(BlueprintType)
enum CurrentState
{
    FLYING,
    FLYING_WHILE_DRIFTING,
    RAGDOLLED,
    DEFAULT,
};

UENUM(BlueprintType)
enum UI_Text
{
    UNINITIALIZED,
    SPEED_TEXT = 0,
    SCANNER_TEXT = 1,
    ALARM_SENSOR = 2,
    BEACON = 3,
    E_WAR = 4,
    THRUSTERS = 5,
    KICK = 6,
    COMPASS = 7,
};

UENUM(BlueprintType)
enum UI_Command_Menu
{
    HIDDEN,
    ALL_ABILITIES_MENU,
    BEACON_MENU,
    E_WAR_MENU,
};

    // FLYING = "FLYING",
    // FLYING_WHILE_DRIFTING = "FLYING_WHILE_DRIFTING",
    // RAGDOLLED = "RAGDOLLED",
    // DEFAULT = "DEFAULT",

    // RACER = FString(TEXT("RACER")),
	// WANTED_RACER = FString(TEXT("WANTED_RACER")),
    // ENVIRONMENT_HAZARD = FString(TEXT("ENVIRONMENT_HAZARD")),
    // BUFF = FString(TEXT("BUFF")),
	// HOSTILE_NPC = FString(TEXT("HOSTILE_NPC")),
	// GOAL = FString(TEXT("GOAL")),
	// EMPTY = FString(TEXT("EMPTY")),
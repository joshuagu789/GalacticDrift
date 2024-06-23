// Copyright Epic Games, Inc. All Rights Reserved.

#include "GalacticDriftGameMode.h"
#include "GalacticDriftCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGalacticDriftGameMode::AGalacticDriftGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

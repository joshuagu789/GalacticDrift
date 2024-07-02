// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Header_Enumerations.h"
#include "Containers/Set.h"
#include "Containers/Array.h"
#include "Class_RacingGameState.generated.h"

/**
 * 
 */
UCLASS()
class GALACTICDRIFT_API AClass_RacingGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Initialization")
	/*
		Returns true if successfully added, otherwise false
			- takes in some reference to some actor
	*/
	bool AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<AActor*> racerList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<AActor*> markerList;
	UPROPERTY()
		int test = 0;
};

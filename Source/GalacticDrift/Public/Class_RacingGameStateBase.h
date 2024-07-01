// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Header_Enumerations.h"
#include "Containers/Set.h"
#include "Containers/Array.h"
#include "Class_RacingGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GALACTICDRIFT_API AClass_RacingGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Initialization")
	/*
		Returns true if successfully added, otherwise false
			- takes in some reference to some actor
	*/
	bool AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<AActor*> racerList;
	UPROPERTY()
		TArray<AActor*> markerList;
};

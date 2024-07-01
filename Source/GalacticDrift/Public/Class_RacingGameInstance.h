// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Header_Enumerations.h"
#include "Containers/Set.h"
#include "Containers/Array.h"
#include "Class_RacingGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GALACTICDRIFT_API UClass_RacingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Initialization")
	/*
		Returns true if successfully added, otherwise false
			- takes in some reference to some actor
	*/
	bool AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor);

	UFUNCTION(BlueprintCallable, Category="Initialization")
		void testprinting();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<AActor*> racerList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> markerList;
	UPROPERTY()
		int test = 0;
};

/*
	Characteristic to describe anything that can show up on entity sensors
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Header_Enumerations.h"
#include "Class_Marker.generated.h"


// UENUM(BlueprintType)
// enum EntityType
// {
//     RACER,
// 	WANTED_RACER,
//     ENVIRONMENT_HAZARD,
//     BUFF,
// 	HOSTILE_NPC,
// 	GOAL,
// 	EMPTY,
// };

// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_Marker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Marker();

    UFUNCTION(BlueprintCallable, Category="Initialization")
		/*
			Returns true if successfully changed type, false otherwise, typically set for any marker in blueprints when they first spawn
		*/
        bool SetType(MarkerType newType);

	UFUNCTION(BlueprintCallable, Category="Initialization")
		FString GetMarkerName();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<MarkerType> type = EMPTY_MARKER;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString markerName = "empty marker name";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool invisible = false;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

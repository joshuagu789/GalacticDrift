/*
	Class not working exactly as intended, feature of not taking damage on spawn is now moved to Class_DamageableActor
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Class_NoHitOnSpawning.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_NoHitOnSpawning : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_NoHitOnSpawning();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool disableThenEnablePhysics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool disableThenEnableHitEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool disableThenEnableOverlapEvents;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPrimitiveComponent* rootPrimitiveComponentPtr;	// expects root component to be primitive

	float timer;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Class_Freezable.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom) )
class GALACTICDRIFT_API UClass_Freezable : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Freezable();

	UFUNCTION(BlueprintCallable)
		void Freeze();
	UFUNCTION(BlueprintCallable)
		void UnFreeze();
	UFUNCTION(BlueprintCallable)
		bool GetIsFrozen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool isFrozen = false;
	int numberOfOptimizersInRange;	// only freeze if zero optimizers in range (cannot freeze if one optimizer leaves and another still remains)
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

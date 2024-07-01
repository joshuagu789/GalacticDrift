/*
  	Any type of damageable component that uses energy, typically does not expect any component to be of this type but rather its children
		- NOTE: all children of equipment are expected to have worse accuracy/performance based on health
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Class_DamageableComponent.h"
#include "Class_Equipment.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom) )
class GALACTICDRIFT_API UClass_Equipment : public UClass_DamageableComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Equipment();

	void TakeDamage(float damage);
	void Repair(float amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float energy = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

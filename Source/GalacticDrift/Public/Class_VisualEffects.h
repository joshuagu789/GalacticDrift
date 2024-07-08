// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// #include "CascadeParticleSystemComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Class_Entity.h"
#include "Class_VisualEffects.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_VisualEffects : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_VisualEffects();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UParticleSystemComponent*> thrusters;
		// TArray<TSubclassOf<UParticleSystemComponent>> thrusters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass_Entity* entityPtr;
	float checkTimer;
	bool thrustersDisabled;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

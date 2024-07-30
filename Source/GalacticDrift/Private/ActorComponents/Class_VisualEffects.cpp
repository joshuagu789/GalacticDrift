// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_VisualEffects.h"

// Sets default values for this component's properties
UClass_VisualEffects::UClass_VisualEffects()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_VisualEffects::BeginPlay()
{
	Super::BeginPlay();

	// ...
	entityPtr = GetOwner()->GetComponentByClass<UClass_Entity>();
}


// Called every frame
void UClass_VisualEffects::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(checkTimer < 0 && entityPtr){

		checkTimer += 0.1;

		if(entityPtr->GetState() == RAGDOLLED && !thrustersDisabled){
			thrustersDisabled = true;
			DisableParticlesOf(thrusters);
			// for(auto &particleComponent: particleComponents){
			// 	particleComponent->EndTrails();
			// }
		}
		else if(entityPtr->GetState() != RAGDOLLED && thrustersDisabled){
			thrustersDisabled = false;
			EnableParticlesOf(thrusters);
			// for(auto &particleComponent: particleComponents){
			// 	particleComponent->BeginTrails();
			// }	
		}
	} else {
		checkTimer -= DeltaTime;
	}
}

void UClass_VisualEffects::DisableParticlesOf(TArray<UParticleSystemComponent*> &particleComponents){
	for(auto &particleComponent: particleComponents){
		particleComponent->EndTrails();
	}
}
void UClass_VisualEffects::EnableParticlesOf(TArray<UParticleSystemComponent*> &particleComponents){
	for(auto &particleComponent: particleComponents){
		particleComponent->BeginTrails("","",ETrailWidthMode_FromCentre,1.0);
	}	
}

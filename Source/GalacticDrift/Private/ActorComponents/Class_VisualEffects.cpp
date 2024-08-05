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
	if(disableOnStart){
		DisableParticlesOf(thrusters);
	    	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("disable thrusters on start in class visual effects"));
	}
	SetComponentTickInterval(0.1);
}


// Called every frame
void UClass_VisualEffects::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(entityPtr){
	    	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("entity PTR???"));

		if(entityPtr->GetState() != FLYING && !thrustersDisabled && entityPtr->GetState() != FLYING_WHILE_DRIFTING){
			thrustersDisabled = true;
			DisableParticlesOf(thrusters);
			// for(auto &particleComponent: particleComponents){
			// 	particleComponent->EndTrails();
			// }
		}
		else if(entityPtr->GetState() == FLYING && thrustersDisabled || entityPtr->GetState() == FLYING_WHILE_DRIFTING && thrustersDisabled){
			thrustersDisabled = false;
			EnableParticlesOf(thrusters);
			// for(auto &particleComponent: particleComponents){
			// 	particleComponent->BeginTrails();
			// }	
		}
	} 
	if(checkTimer > 0){
		checkTimer -= DeltaTime;
		if(checkTimer <= 0){
			thrustersDisabled = true;
			DisableParticlesOf(thrusters);
	    	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("disable thrusters with check timer class visual effects"));
		}
	}
}

void UClass_VisualEffects::DisableParticlesOf(TArray<UParticleSystemComponent*> &particleComponents){
	    	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("disable thrusters in class visual effects 2"));
	for(auto &particleComponent: particleComponents){
		particleComponent->EndTrails();
	}
}
void UClass_VisualEffects::EnableParticlesOf(TArray<UParticleSystemComponent*> &particleComponents){
	    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("enable thrusters in class visual effects"));
	for(auto &particleComponent: particleComponents){
		particleComponent->BeginTrails("","",ETrailWidthMode_FromCentre,1.0);
	}	
}

void UClass_VisualEffects::EnableParticlesFor(float duration){
	if(duration <= 0){
	    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("invalid duration for enableparticlesfor in class visual effects"));
	}

	checkTimer = duration;
	thrustersDisabled = false;
	EnableParticlesOf(thrusters);
	    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("enable thrusters in class visual effects"));

}

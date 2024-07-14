// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_NoHitOnSpawning.h"

// Sets default values for this component's properties
UClass_NoHitOnSpawning::UClass_NoHitOnSpawning()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_NoHitOnSpawning::BeginPlay()
{
	Super::BeginPlay();

	// ...
	timer = duration;

	if(!rootPrimitiveComponentPtr){
		rootPrimitiveComponentPtr = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		if(!rootPrimitiveComponentPtr){
        	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: rootPrimitiveComponentPtr is nullptr in Class_NoHitOnSpawning"));	
		}
	}
	if(rootPrimitiveComponentPtr){
		if(disableThenEnablePhysics){
			rootPrimitiveComponentPtr->SetSimulatePhysics(false);
		}
		if(disableThenEnableHitEvents){
			rootPrimitiveComponentPtr->SetNotifyRigidBodyCollision(false);
		}
		if(disableThenEnableOverlapEvents){
			rootPrimitiveComponentPtr->SetGenerateOverlapEvents(false);
		}
	}
	
}


// Called every frame
void UClass_NoHitOnSpawning::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(timer > 0.1){
		timer-=DeltaTime;
		
		if(timer <= 0 && rootPrimitiveComponentPtr){
			if(disableThenEnablePhysics){
				rootPrimitiveComponentPtr->SetSimulatePhysics(true);
			}
			if(disableThenEnableHitEvents){
				rootPrimitiveComponentPtr->SetNotifyRigidBodyCollision(true);
			}
			if(disableThenEnableOverlapEvents){
				rootPrimitiveComponentPtr->SetGenerateOverlapEvents(true);
			}
		}
		else if(timer <= 0){
	        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: rootPrimitiveComponentPtr is nullptr in Class_NoHitOnSpawning"));	
		}
	}
}


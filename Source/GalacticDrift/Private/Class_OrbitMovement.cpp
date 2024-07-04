// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_OrbitMovement.h"

// Sets default values for this component's properties
UClass_OrbitMovement::UClass_OrbitMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_OrbitMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_OrbitMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(isOrbiting && orbitTarget){
		FVector destination = currentTargetOffset + orbitTarget->GetRootComponent()->K2_GetComponentLocation();
		FVector position = GetOwner()->GetRootComponent()->K2_GetComponentLocation();

		if(FVector::DistSquared(destination, position) <= 100){
			currentTargetOffset = angleOfOrbit.RotateVector(currentTargetOffset);
		}
		else if(moveComponentPtr){
			// moveComponentPtr->AddInputVector(destination, true);
			moveComponentPtr->AddInputVector(destination - position, true);
		} else {
        	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor is nullptr in BeginOrbiting parameter of Class OrbitMovement"));	
		}
	}
}

void UClass_OrbitMovement::BeginOrbiting(AActor* actor){
	if(actor){
		orbitTarget = actor;
		isOrbiting = true;

		angleOfOrbit.Pitch = UKismetMathLibrary::RandomFloatInRange(-1,1);
		angleOfOrbit.Roll = UKismetMathLibrary::RandomFloatInRange(-1,1);
		angleOfOrbit.Yaw = UKismetMathLibrary::RandomFloatInRange(-1,1);

		currentTargetOffset = GetOwner()->GetRootComponent()->K2_GetComponentLocation() - actor->GetRootComponent()->K2_GetComponentLocation();
		currentTargetOffset = currentTargetOffset.GetSafeNormal() * orbitRange;
	} else {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor is nullptr in BeginOrbiting parameter of Class OrbitMovement"));
	}
}

void UClass_OrbitMovement::StopOrbiting(){
	orbitTarget = nullptr;
	isOrbiting = false;
}

bool UClass_OrbitMovement::IsOrbiting(){ return isOrbiting; }


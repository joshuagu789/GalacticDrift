// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Swivel.h"

// Sets default values for this component's properties
UClass_Swivel::UClass_Swivel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Swivel::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_Swivel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(isRotating && rotateTarget){
		FRotator destinationRotation = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetRootComponent()->K2_GetComponentLocation(), rotateTarget->GetRootComponent()->K2_GetComponentLocation());
		FHitResult dummy;
		// GetOwner()->GetRootComponent()->K2_SetWorldRotation(requiredRotation, true, dummy, true);
		FRotator currentRotation = GetOwner()->GetRootComponent()->K2_GetComponentRotation();
		// GetOwner()->GetRootComponent()->K2_AddWorldRotation( 10 * DeltaTime * (destinationRotation - currentRotation), true, dummy, true);

		// warning: entity sometimes spazzes out after rotating in complete circle, probably because some issue of adding rotation over 360 or under 0
		GetOwner()->GetRootComponent()->K2_AddRelativeRotation( 10 * DeltaTime * (destinationRotation - currentRotation), true, dummy, true);
	}
}

void UClass_Swivel::BeginFacing(AActor* actor){
	if(actor){
		rotateTarget = actor;
		isRotating = true;
	} else {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor is nullptr in BeginFacing parameter of Class Swivel"));
	}
}

void UClass_Swivel::StopRotating(){
	rotateTarget = nullptr;
	isRotating = false;
}


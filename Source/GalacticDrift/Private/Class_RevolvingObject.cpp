// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_RevolvingObject.h"

// Sets default values for this component's properties
UClass_RevolvingObject::UClass_RevolvingObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	componentOwner = GetOwner();
	tickFrequency = GetComponentTickInterval();
	// if(!revolveTarget){
	// 	revolveTarget = owner;
	// }
}


// Called when the game starts
void UClass_RevolvingObject::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_RevolvingObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(revolveTarget && revolveTarget != componentOwner){
		revolver *= DeltaTime;
		// vectorFromRevolveTarget = GetOwner()->GetActorLocation() - revolveTarget->GetActorLocation();
		vectorFromRevolveTarget = revolver.RotateVector(vectorFromRevolveTarget);

		revolver *= 1/DeltaTime;

		FHitResult dummy;
        // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("revolving"));
		// GetOwner()->GetRootComponent()->SetWorldLocation(revolveTarget->GetRootComponent()->GetComponentLocation() + vectorFromRevolveTarget, false, dummy, ETeleportType::None);
		// GetOwner()->SetActorLocation(revolveTarget->GetRootComponent()->GetComponentLocation() + vectorFromRevolveTargetNormalized, false, dummy, ETeleportType::None);
		
		// GetOwner()->SetActorLocation(revolveTarget->GetRootComponent()->GetComponentLocation() + vectorFromRevolveTarget, true, dummy, ETeleportType::None);
		// GetOwner()->K2_SetActorLocation(revolveTarget->GetRootComponent()->GetComponentLocation() + vectorFromRevolveTarget, false, dummy, true);
		// GetOwner()->K2_SetActorLocation(revolveTarget->GetActorLocation() + vectorFromRevolveTarget, false, dummy, true);

		// if(!test){
		// 	test = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		// }	
		// if(test){
		// 	FVector direction = revolveTarget->GetRootComponent()->GetComponentLocation() + vectorFromRevolveTarget - GetOwner()->GetRootComponent()->GetComponentLocation();
		// 	direction = direction.GetSafeNormal();
		// 	test->AddForce(1000 * FVector{-1,0,0}, "", true);
		// }
		if(moveComponentPtr){
			moveComponentPtr->AddInputVector(revolveTarget->GetActorLocation() + vectorFromRevolveTarget - GetOwner()->GetActorLocation(), true);
		}
	}
}

void UClass_RevolvingObject::Freeze(){ 
	// SetComponentTickInterval(0.5); 
}

void UClass_RevolvingObject::UnFreeze(){ 
	// SetComponentTickInterval(tickFrequency); 
}

void UClass_RevolvingObject::SetRevolveTarget(AActor* target, float pitch, float roll, float yaw){
	if(!target){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: target is nullptr in UClass_RevolvingObject::SetRevolveTarget"));
		return;	
	}
	revolveTarget = target;
	revolver.Pitch = pitch;
	revolver.Roll = roll;
	revolver.Yaw = yaw;
	revolveLocation = target->GetRootComponent()->GetComponentLocation();
	vectorFromRevolveTarget = GetOwner()->GetActorLocation() - target->GetActorLocation();
	// vectorFromRevolveTarget = GetOwner()->GetRootComponent()->GetComponentLocation() - target->GetRootComponent()->GetComponentLocation();
}

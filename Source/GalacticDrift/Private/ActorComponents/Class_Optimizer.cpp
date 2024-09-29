// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_Optimizer.h"

// Sets default values for this component's properties
UClass_Optimizer::UClass_Optimizer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Optimizer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// actorCollider = GetOwner();
	// if(collider){
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("initialize overlap"));
	// 	// collider->OnComponentBeginOverlap.AddDynamic(this, &UClass_Optimizer::OnComponentBeginOverlap);
	// }
	// actorCollider->OnActorBeginOverlap.AddDynamic(this, &UClass_Optimizer::OnActorBeginOverlap);
}


// Called every frame
void UClass_Optimizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UClass_Optimizer::AttemptToEnableActor(AActor* actor){
	if(!actor){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor is null in AttemptToEnableActor for Class_Optimizer"));
	}
	// TInlineComponentArray<UClass_Freezable*> components(actor);	// is this necessary? this done to avoid memory allocation costs, but there not much freezable components to begin with
	TInlineComponentArray<UClass_Freezable*, 10> components;	// reserve 10 for now

	actor->GetComponents<UClass_Freezable>(components, true);

	for(UClass_Freezable* component: components){
		component->AddOptimizerInRange();
	}
}

void UClass_Optimizer::AttemptToDisableActor(AActor* actor){
	if(!actor){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor is null in AttemptToDisableActor for Class_Optimizer"));
	}
	TInlineComponentArray<UClass_Freezable*, 10> components;	// reserve 10 for now

	actor->GetComponents<UClass_Freezable>(components, true);

	for(UClass_Freezable* component: components){
		component->RemoveOptimizerInRange();
	}
}

// void UClass_Optimizer::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
// 									bool bFromSweep, const FHitResult& SweepResult){
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OVERLLAPPINGGG"));
// 	// Super::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// }

// void UClass_Optimizer::OnActorBeginOverlap(AActor* OtherActor){
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("u shall work!"));
// }

// void UClass_Optimizer::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){

// }	

// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Freezable.h"

// Sets default values for this component's properties
UClass_Freezable::UClass_Freezable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Freezable::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(freezeOnPlay){
		Freeze();
	}
	
}


// Called every frame
void UClass_Freezable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClass_Freezable::Freeze(){ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: there typically shouldn't be instances of UClass_Freezable instead of a child class")); }

void UClass_Freezable::UnFreeze(){ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: there typically shouldn't be instances of UClass_Freezable instead of a child class")); }

bool UClass_Freezable::GetIsFrozen(){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: there typically shouldn't be instances of UClass_Freezable instead of a child class"));
	return isFrozen; 
}

void UClass_Freezable::AddOptimizerInRange(){
	numberOfOptimizersInRange++;
	if(numberOfOptimizersInRange == 1){
		UnFreeze();
	}
}	

void UClass_Freezable::RemoveOptimizerInRange(){
	numberOfOptimizersInRange--;
	if(numberOfOptimizersInRange == 0){
		Freeze();
	}
	else if(numberOfOptimizersInRange < 0){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: numberOfOptimizersInRange is negative for Class_Freezable after RemoveOptimizerInRange call"));
	}
}	

// bool UClass_Freezable::HasNoOptimizersInRange(){
// 	if(numberOfOptimizersInRange < 0){
// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: numberOfOptimizersInRange is negative for Class_Freezable"));
// 	}

// 	return numberOfOptimizersInRange == 0;
// }
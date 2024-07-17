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
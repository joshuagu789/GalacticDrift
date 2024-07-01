// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Equipment.h"

// Sets default values for this component's properties
UClass_Equipment::UClass_Equipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Equipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_Equipment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClass_Equipment::TakeDamage(float damage){ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: there typically shouldn't be instances of UClass_Equipment instead of a child class")); }
void UClass_Equipment::Repair(float amount) {GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: there typically shouldn't be instances of UClass_Equipment instead of a child class")); }
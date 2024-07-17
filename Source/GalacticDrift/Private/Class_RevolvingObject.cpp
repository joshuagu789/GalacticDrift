// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_RevolvingObject.h"

// Sets default values for this component's properties
UClass_RevolvingObject::UClass_RevolvingObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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
}

void UClass_RevolvingObject::Freeze(){}

void UClass_RevolvingObject::UnFreeze(){}
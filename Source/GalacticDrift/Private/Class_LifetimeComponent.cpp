// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_LifetimeComponent.h"

// Sets default values for this component's properties
UClass_LifetimeComponent::UClass_LifetimeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_LifetimeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetComponentTickInterval(1);
}


// Called every frame
void UClass_LifetimeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(lifeTime > 0){
		lifeTime -= DeltaTime;
		if(lifeTime <= 0){
			GetOwner()->K2_DestroyActor();
		}
	}
}

void UClass_LifetimeComponent::SetLifetime(float time){ lifeTime = time; }

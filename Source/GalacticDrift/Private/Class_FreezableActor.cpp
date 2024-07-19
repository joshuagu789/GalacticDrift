// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_FreezableActor.h"

// Sets default values for this component's properties
UClass_FreezableActor::UClass_FreezableActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_FreezableActor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_FreezableActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClass_FreezableActor::Freeze(){
	TSet<UActorComponent*> components = GetOwner()->GetComponents();

	for(UActorComponent* component: components){
		UClass_Freezable* freezable = Cast<UClass_Freezable>(component);
		if(!freezable){
			component->SetComponentTickEnabled(false);
		}
		component->SetComponentTickEnabled(false);
	}
	GetOwner()->SetActorTickEnabled(false);	

	if(makeActorInvisibleOnFreeze){
		GetOwner()->SetActorHiddenInGame(true);
	}
	SetComponentTickEnabled(false);
}

void UClass_FreezableActor::UnFreeze(){
	GetOwner()->SetActorTickEnabled(true);

	TSet<UActorComponent*> components = GetOwner()->GetComponents();
	for(UActorComponent* component: components){
		component->SetComponentTickEnabled(true);
	}

	if(makeActorInvisibleOnFreeze){
		GetOwner()->SetActorHiddenInGame(false);
	}
	SetComponentTickEnabled(true);
}
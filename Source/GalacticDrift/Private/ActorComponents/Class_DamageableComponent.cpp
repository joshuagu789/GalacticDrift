// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_DamageableComponent.h"

// Sets default values for this component's properties
UClass_DamageableComponent::UClass_DamageableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_DamageableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	health = maxHealth;
}


// Called every frame
void UClass_DamageableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClass_DamageableComponent::TakeDamage(float damage){ 
	if(damage <= 0){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("why damage <= 0 in takedamage of class damageablecomponent"));
	}
	health -= damage;
}

void UClass_DamageableComponent::Repair(float amount){ 
	health = (health + amount <= maxHealth) ? (health + amount) : (maxHealth);
}

void UClass_DamageableComponent::FullRepair(){ 
	health = maxHealth;
}
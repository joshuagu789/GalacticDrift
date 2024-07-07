// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_DamageableActor.h"

// Sets default values for this component's properties
UClass_DamageableActor::UClass_DamageableActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_DamageableActor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_DamageableActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UClass_DamageableActor::CalculateAndApplyDamage(){
	float damage = GetOwner()->GetRootComponent()->GetComponentVelocity().Size() * 0.1;
	health -= damage;
	return damage;
}

TEnumAsByte<DamageableActor_Type> UClass_DamageableActor::GetType(){ return type; }

bool UClass_DamageableActor::IsDestroyed(){ return health <= 0; }


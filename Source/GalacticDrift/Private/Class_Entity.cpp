// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Entity.h"

// Sets default values for this component's properties
UClass_Entity::UClass_Entity()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Entity::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_Entity::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<TEnumAsByte<EntityType>> UClass_Entity::GetEnemyTypes(){
	TArray<TEnumAsByte<EntityType>> temp;
	switch(type){
		case RACER:
			break;
		case NPC_FACTION0:
			temp.Add(RACER);
			break;
	}
	return temp;
}

TEnumAsByte<EntityState> UClass_Entity::GetState(){ return state; }

void UClass_Entity::SetState(TEnumAsByte<EntityState> newState){ state = newState; }


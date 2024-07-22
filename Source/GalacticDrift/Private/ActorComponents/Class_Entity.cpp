// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_Entity.h"

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
	SetComponentTickEnabled(false);
	
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

bool UClass_Entity::IsEnemyWith(TEnumAsByte<EntityType> otherEntity){
	switch(type){
		case FRIENDLY_NPC:
			if(otherEntity == NPC_FACTION0)
				return true;
			return false;
	}
	return false;
}
bool UClass_Entity::IsFriendlyWith(TEnumAsByte<EntityType> otherEntity){
	if(otherEntity == type){
		return true;
	}
	switch(type){
		case FRIENDLY_NPC:
			if(otherEntity == FRIENDLY_NPC || otherEntity == RACER)
				return true;
			return false;
		case RACER:
			if(otherEntity == FRIENDLY_NPC || otherEntity == RACER)
				return true;
			return false;
	}
	return false;
}


TEnumAsByte<EntityState> UClass_Entity::GetState(){ return state; }

TEnumAsByte<EntityType> UClass_Entity::GetType(){ return type; };

void UClass_Entity::SetState(TEnumAsByte<EntityState> newState){ state = newState; }


// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_GameServer.h"

// Sets default values
AClass_GameServer::AClass_GameServer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_GameServer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClass_GameServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AClass_GameServer::AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor){
	if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity tried to send empty actor pointer to game server"));
		return false;
	}
	if(type == MARKER){
		if(markerList.Contains(actor)){
        	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity already added to game server"));
			return false;
		} else 
			markerList.Add(actor);
	}
	return false;
}
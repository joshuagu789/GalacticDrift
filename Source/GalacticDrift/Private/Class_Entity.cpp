// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Entity.h"

// Sets default values
AClass_Entity::AClass_Entity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_Entity::BeginPlay()
{
	Super::BeginPlay();
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("trying to add to server"));
	// server = Cast<UClass_RacingGameInstance>(UGameplayStatics::GetGameInstance( GetOwner() ));
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("success?"));
	// server->testprinting();
	// server->AddEntityToServer(type, this);
	// if(server)
	// 	server->AddEntityToServer(type, self);
	// else
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity's server pointer is null, cannot add to server"));
	// if(server)
	// 	server->AddEntityToServer(type, self);
	// else
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity's server pointer is null, cannot add to server"));
}

// Called every frame
void AClass_Entity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AClass_Entity::AddToServer(AActor* actor){
	if(server)
		// return server->GetClass()->AddEntityToServer(type, actor);	// should have checker to make sure GetClass returns gameserver class
		return true;
	else
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity's server pointer is null, cannot add to server"));
	return false;
}


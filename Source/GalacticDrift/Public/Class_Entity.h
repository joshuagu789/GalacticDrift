/*
	Any actor that needs to be registered with the game state for quick access to stuff
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_RacingGameInstance.h"
#include "Header_Enumerations.h"
#include "Kismet/GameplayStatics.h"
#include "Class_Entity.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Entity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_Entity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "AClass_GameServer"))
		// AActor* server;	// pointer to actor in game that contains class AClass_GameServer
		UClass_RacingGameInstance* server;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EntityType> type;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Initialization")
		bool AddToServer(AActor* actor); 

};

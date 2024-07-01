// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Header_Enumerations.h"
#include "Class_GameServer.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_GameServer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_GameServer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<AActor*> racerList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<AActor*> markerList;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		/*
			Returns true if successfully added, otherwise false
				- takes in some reference to some actor
		*/
		bool AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor);
};

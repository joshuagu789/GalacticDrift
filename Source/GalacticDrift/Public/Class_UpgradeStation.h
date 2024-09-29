// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Rewarder.h"
#include "Class_UpgradeStation.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_UpgradeStation : public AClass_Rewarder
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_UpgradeStation();

	void RewardRacer(AClass_Racer_Pawn* racer) override;
	void RevealToRacers(const TSet<AActor*>& racers) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

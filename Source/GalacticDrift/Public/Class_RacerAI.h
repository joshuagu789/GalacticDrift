// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Class_Racer_Pawn.h"
#include "Class_RacerAI.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_RacerAI : public AClass_Racer_Pawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AClass_RacerAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		AActor* destination;
	// UPROPERTY()
	// 	AActor* enemy;
private:
	void DriftTowardsDestination();
	bool AcquireDestination();
	void ToggleAggression();


	float decisionTimer = 4;
	//float aggressionTimer = 0;	// 0 means not aggressive, positive means time left of aggression
	bool isAggressive;
	float timeAggressive = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

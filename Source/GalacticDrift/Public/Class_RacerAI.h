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

private:
	void DriftTowards(FVector location);
	bool AcquireDestination();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

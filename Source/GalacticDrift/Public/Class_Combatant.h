// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Class_Combatant.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Combatant : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AClass_Combatant();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* target;

	UFUNCTION(BlueprintCallable)
		bool HasTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

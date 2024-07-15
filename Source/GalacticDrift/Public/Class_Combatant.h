// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// #include "Containers/Array.h"
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
	UFUNCTION(BlueprintCallable)
		bool HasBackupTargets();
	UFUNCTION(BlueprintCallable)
		bool IsDespawning();
	UFUNCTION(BlueprintCallable)
		/*
		Returns false if already has actor as target, also targets actor as if cyclenexttarget was called
		*/
		bool AddTarget(AActor* actor);
	UFUNCTION(BlueprintCallable)
		void RemoveTarget(AActor* actor);
	UFUNCTION(BlueprintCallable)
		/*
		Finds next possible target in targetList while removing any pending kill actors along the way
			returns true if found a new target, false if no more targets
		*/
		bool CycleNextTarget();
	UFUNCTION(BlueprintCallable)
		bool HasActorInTargetList(AActor* actor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> targetList;	// maybe tset instead?

	bool despawning;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

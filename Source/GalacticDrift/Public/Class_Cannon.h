/*
	Anything that launches projectiles
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class_Equipment.h"
#include "Class_Empty.h"
#include "Class_Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Class_Cannon.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_Cannon : public UClass_Equipment
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void BeginAttacking(AActor* actor);	
	UFUNCTION(BlueprintCallable)
		void StopAttacking();	
	UFUNCTION(BlueprintCallable)
		bool IsAttacking();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AClass_Projectile> projectilePtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UClass_Empty*> bulletSpawnPoints;	// expects BP_Cannon to initialize
		// TArray<USceneComponent*> bulletSpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float angleToFire = 90;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float projectileSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float timeBetweenEachTurret;	// if shoots x bullets per attack, how long to wait between each shot

	UPROPERTY()
		AActor* attackTarget;
	bool isAttacking;
	float cooldownTimer;
	float timeBetweenEachTurretTimer;
	int turretIndex;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};

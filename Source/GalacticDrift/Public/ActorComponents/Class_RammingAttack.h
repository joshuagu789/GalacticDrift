// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Class_Attack.h"
#include "Class_Entity.h"
#include "Class_DamageableActor.h"
#include "Class_RammingAttack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALACTICDRIFT_API UClass_RammingAttack : public UClass_Attack
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_RammingAttack();

    void BeginAttacking(AActor* actor) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float immunityDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float massMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float originalMassScale = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float collisionRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* skeletalMeshPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass_DamageableActor* damageComponentPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass_Entity* entityPtr;
	
	UPROPERTY()
		USphereComponent* ramCollider;
	float attackDelayTimer = 0;
	float immunityDurationTimer = 0;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

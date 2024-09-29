// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Class_Equipment.h"
#include "Class_Attack.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom) )
class GALACTICDRIFT_API UClass_Attack : public UClass_Equipment
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Attack();

	UFUNCTION(BlueprintCallable)
		virtual void BeginAttacking(AActor* actor);	
	UFUNCTION(BlueprintCallable)
		virtual void StopAttacking();	
	UFUNCTION(BlueprintCallable)
		virtual bool IsAttacking();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		AActor* attackTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float cooldown;

	bool isAttacking;
	float cooldownTimer;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

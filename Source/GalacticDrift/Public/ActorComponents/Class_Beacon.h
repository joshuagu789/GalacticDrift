// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Class_Equipment.h"
#include "Class_Swivel.h"
#include "Class_OrbitMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Class_Beacon.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_Beacon : public UClass_Equipment
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Beacon();

	UFUNCTION(BlueprintCallable)
		void SpawnFan();
	UFUNCTION(BlueprintCallable)
		void SpawnPolice();
	UFUNCTION(BlueprintCallable)
		void SpawnAttacker(AActor* target);

	UFUNCTION(BlueprintCallable)
		bool CanSpawnFan();
	UFUNCTION(BlueprintCallable)
		bool CanSpawnPolice();
	UFUNCTION(BlueprintCallable)
		bool CanSpawnAttacker();

	UFUNCTION(BlueprintCallable)
		float GetFanCooldown();
	UFUNCTION(BlueprintCallable)
		float GetPoliceCooldown();
	UFUNCTION(BlueprintCallable)
		float GetAttackerCooldown();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> fanPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> policePtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> attackerPtr;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fanCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float policeCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackerCooldown;

	float fanTimer;
	float policeTimer;
	float attackerTimer;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class_Equipment.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Class_OrbitMovement.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_OrbitMovement : public UClass_Equipment
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_OrbitMovement();

	UFUNCTION(BlueprintCallable)
		void BeginOrbiting(AActor* actor);
	UFUNCTION(BlueprintCallable)
		/*
		Beware of null pointers
		*/
		AActor* GetOrbitTarget();
	UFUNCTION(BlueprintCallable)
		void StopOrbiting();
	UFUNCTION(BlueprintCallable)
		bool IsOrbiting();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UFloatingPawnMovement* moveComponentPtr;

	UPROPERTY()
		AActor* orbitTarget;
	UPROPERTY()
		FVector currentTargetOffset;

	UPROPERTY()
		FRotator angleOfOrbit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int orbitRange;

	bool isOrbiting;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

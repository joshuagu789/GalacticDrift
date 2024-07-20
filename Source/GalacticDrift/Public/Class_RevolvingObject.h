// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Class_Freezable.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
// #include "GameFramework/RotatingMovementComponent.h"
#include "Class_RevolvingObject.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_RevolvingObject : public UClass_Freezable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_RevolvingObject();

	void Freeze() override;
	void UnFreeze() override;

	UFUNCTION(BlueprintCallable)
		void SetRevolveTarget(AActor* target, float pitch, float roll, float yaw);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rotateSpeed = 0;	// will not rotate upon itself if rotateSpeed is zero	

    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //     UFloatingPawnMovement* moveComponentPtr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UFloatingPawnMovement* moveComponentPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPrimitiveComponent* test;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* revolveTarget;
	UPROPERTY()
		FVector revolveLocation;
	UPROPERTY()
		AActor* componentOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector vectorFromRevolveTarget;
	UPROPERTY()
		FRotator revolver;
	UPROPERTY()
		FRotator rotater;

	float tickFrequency;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

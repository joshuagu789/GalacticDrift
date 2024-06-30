// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Ragdollable.h"
#include "Class_ActorInformationTracker.h"
#include "Math/Rotator.h"
#include "Class_Racer_Pawn.generated.h"

UENUM(BlueprintType)
enum CurrentState
{
    FLYING,
    FLYING_WHILE_DRIFTING,
    RAGDOLLED,
    DEFAULT,
};

UCLASS()
class GALACTICDRIFT_API AClass_Racer_Pawn : public APawn, public IRagdollable, public IClass_ActorInformationTracker
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AClass_Racer_Pawn();

    UFUNCTION(BlueprintCallable, Category="Movement")
        void StartFlying(float initialSpeed, bool accelerate, float floppiness);

    UFUNCTION(BlueprintCallable, Category="Movement")
        bool CanDrift();
    UFUNCTION(BlueprintCallable, Category="Movement")
        void DriftUp(float rotateSpeed);
    UFUNCTION(BlueprintCallable, Category="Movement")
        void DriftLeft(float rotateSpeed);
    UFUNCTION(BlueprintCallable, Category="Movement")
        void DriftDown(float rotateSpeed);
    UFUNCTION(BlueprintCallable, Category="Movement")
        void DriftRight(float rotateSpeed);
    UFUNCTION(BlueprintCallable, Category="Movement")
        void StopDrift();
    
    UFUNCTION(BlueprintCallable, Category="Action")
        void StunFor(float duration);
    
    // From interfaces
    void RagdollFor(float duration);
    void UnRagdoll();
    FString GetSpeedIntAsString();
    float GetSpeedFloat(int decimalPlaces);
    int GetSpeedInt();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere)
        float speed = 0;
    
    CurrentState state = DEFAULT;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UFloatingPawnMovement* moveComponentPtr;    // floating pawn movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        USkeletalMeshComponent* skeletalMeshPtr;
    
    float popularity = 0;
    bool isAccelerating = false;
    FRotator rotation = {0,0,0};
    
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "Racer.generated.h"


UCLASS()
class GALACTICDRIFT_API ARacer : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ARacer();

    UFUNCTION(BlueprintCallable, Category="Movement")
        void SetVelocity(float velocity);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<UPrimitiveComponent> collider;
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere)
        float speed = 0;
    
    //    UPROPERTY(EditAnywhere)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UCapsuleComponent* colliderPtr;
//    UPrimitiveComponent* collider;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

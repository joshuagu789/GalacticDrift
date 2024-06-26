// Fill out your copyright notice in the Description page of Project Settings.


#include "Racer.h"
//#include "Engine/Source/Runtime/Engine/Classes/Components/PrimitiveComponent.h"

// Sets default values
ARacer::ARacer()
{
     // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARacer::BeginPlay()
{
    Super::BeginPlay();
    colliderPtr = GetCapsuleComponent();
}

// Called every frame
void ARacer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARacer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*
 Specifically sets the velocity of racer's capsule in the forward vector direction
 */
void ARacer::SetVelocity(float velocity)
{
    if(colliderPtr)
        colliderPtr->SetPhysicsLinearVelocity( GetActorForwardVector() * 1000, false);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Racer_Pawn.h"

/*
 Expects all variables to be initialized in blueprint
 */
AClass_Racer_Pawn::AClass_Racer_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
//    moveComponentPtr = FindComponentByClass<UFloatingPawnMovement>();
//    moveComponentPtr = GetMovementComponent();
//    skeletalMeshPtr = FindComponentByClass<USkeletalMeshComponent>();
}

// Called when the game starts or when spawned
void AClass_Racer_Pawn::BeginPlay()
{
	Super::BeginPlay();
//    moveComponentPtr = GetMovementComponent();
//    skeletalMeshPtr = FindComponentByClass<USkeletalMeshComponent>();
}

// Called every frame
void AClass_Racer_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(state == FLYING){
        moveComponentPtr->AddInputVector(GetActorForwardVector() * speed, isAccelerating);
    }
}

// Called to bind functionality to input
void AClass_Racer_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*
 Sets up for the movement of racer- NOTE actual movement is called in Tick
    initialValue: initial speed to be at
    accelerate: if should speed up over time
    floppiness: how floppy mesh is while flying (0 no floppy, 1 complete flop)
 */
void AClass_Racer_Pawn::StartFlying(float initialSpeed, bool accelerate, float floppiness)
{
//    if(state == FLYING && GEngine)
//        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, ["Warning: StartFlying called when already flying, function cancelled"]);
    UE_LOG(LogTemp, Warning, TEXT("I HAVE BEEN CALLED"));
    UE_LOG(LogTemp, Warning, TEXT("The skeletal mesh is is %s"), ( skeletalMeshPtr ? TEXT("true"): TEXT("false") ));
    if(skeletalMeshPtr){
        UE_LOG(LogTemp, Warning, TEXT("Warning: Pointer for SkeletalMesh is null, function cancelled"));
    }
    if(state == FLYING){
        UE_LOG(LogTemp, Warning, TEXT("Warning: StartFlying called when already flying, function cancelled"));
    } else if(moveComponentPtr){
        UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), ( state == FLYING ? TEXT("true"): TEXT("false") ));
        state = FLYING;
//        moveComponentPtr->AddInputVector(GetActorForwardVector() * initialValue, accelerate);
        isAccelerating = accelerate;
        speed = initialSpeed;
        skeletalMeshPtr->SetPhysicsBlendWeight(floppiness);
        if(initialSpeed > 1 || initialSpeed < 0)
            UE_LOG(LogTemp, Warning, TEXT("Warning: initial speed not between zero and one"));
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("Warning: Pointer for UFloatingPawnMovement is null, function cancelled"));
    }
}

void AClass_Racer_Pawn::StunFor(float duration)
{
    
}


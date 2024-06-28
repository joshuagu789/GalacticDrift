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

    if(state == FLYING){
        UE_LOG(LogTemp, Warning, TEXT("Warning: StartFlying called when already flying, method cancelled"));
    } else if(moveComponentPtr){

        state = FLYING;

        isAccelerating = accelerate;
        speed = initialSpeed;
        
        if(skeletalMeshPtr){
            skeletalMeshPtr->SetPhysicsBlendWeight(floppiness);
        }
        else{ UE_LOG(LogTemp, Warning, TEXT("Warning: Pointer for USkeletalMeshComponent is null, method cancelled")); }
        if(initialSpeed > 1 || initialSpeed < 0)
            UE_LOG(LogTemp, Warning, TEXT("Warning: initial speed not between zero and one"));
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("Warning: Pointer for UFloatingPawnMovement is null, method cancelled"));
    }
}

void AClass_Racer_Pawn::StunFor(float duration)
{
    
}

void AClass_Racer_Pawn::RagdollFor(float duration){
    state = RAGDOLLED;
    if(skeletalMeshPtr){
        skeletalMeshPtr->SetPhysicsBlendWeight(1.0f);
        skeletalMeshPtr->SetAllBodiesSimulatePhysics(true);
    }
    else{ UE_LOG(LogTemp, Warning, TEXT("Warning: Pointer for USkeletalMeshComponent is null, method cancelled")); }
}

void AClass_Racer_Pawn::UnRagdoll(){
    if(skeletalMeshPtr){
//        AActor::K2_SetActorLocationAndRotation(skeletalMeshPtr->GetComponentLocation())
        FHitResult dummy;
//        AActor::K2_SetActorLocation(skeletalMeshPtr->GetComponentLocation(), false, dummy, true);
        AActor::K2_SetActorLocation(skeletalMeshPtr->GetSkeletalCenterOfMass(), false, dummy, true);
        
        skeletalMeshPtr->ResetAllBodiesSimulatePhysics();
        skeletalMeshPtr->SetPhysicsBlendWeight(0.1f);
        state = FLYING;

    }
    else{ UE_LOG(LogTemp, Warning, TEXT("Warning: Pointer for USkeletalMeshComponent is null, method cancelled")); }
}

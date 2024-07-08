// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Racer_Pawn.h"
#include "Kismet/KismetMathLibrary.h"

using namespace std;

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
    if(CanDrift()){
        moveComponentPtr->AddInputVector(GetActorForwardVector() * speed, isAccelerating);
        if(entityPtr->GetState() != FLYING_WHILE_DRIFTING){
//            if(rotation.Roll > 2 || rotation.Roll < 2 && rotation.Pitch > 2 || rotation.Pitch < 2){
            if(rotation.Roll > 2 || rotation.Roll < 2){
                rotation.Roll += -3 * rotation.Roll * DeltaTime;
//                rotation.Pitch += -3 * rotation.Pitch * DeltaTime;
                FHitResult dummy;
    //            rotation.Roll += 10.0;
                AActor::K2_SetActorRelativeRotation(rotation, true, dummy, true);
            }
        }
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
    
    if(entityPtr && entityPtr->GetState() == FLYING){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: StartFlying called when already flyin for Class_Racer_Pawn, method cancelled"));
    } else if(entityPtr && moveComponentPtr){

        // state = FLYING;
        entityPtr->SetState(FLYING);

        isAccelerating = accelerate;
        speed = initialSpeed;
        
        if(skeletalMeshPtr){
            skeletalMeshPtr->SetPhysicsBlendWeight(floppiness);
        }
        else{ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for USkeletalMeshComponent for Class_Racer_Pawn is null, method cancelled")); }
        if(initialSpeed > 1 || initialSpeed < 0)
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: initial speed not between zero and one for Class_Racer_Pawn"));
    }
    else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for UFloatingPawnMovement is null for Class_Racer_Pawn, method cancelled"));
    }
}

bool AClass_Racer_Pawn::CanDrift()
{
    if(entityPtr && entityPtr->GetState() == FLYING || entityPtr->GetState() == FLYING_WHILE_DRIFTING)
        return true;
    return false;
}

/*
 The four drift scripts expect the blueprint to manage if legal to drift usually by calling CanDrift before
    - also expected to be called with delta time
    - also expect the rotateSpeed to be positive
 */
void AClass_Racer_Pawn::DriftUp(float rotateSpeed)
{
    if(CanDrift()){
        // state = FLYING_WHILE_DRIFTING;
        entityPtr->SetState(FLYING_WHILE_DRIFTING);

//        if(rotation.Pitch <= 90){
        if(true){
            rotation.Pitch += rotateSpeed;
            if(rotation.Pitch >= 360)
                rotation.Pitch = rotation.Pitch - 360;
            FHitResult dummy;
            AActor::K2_SetActorRelativeRotation(rotation, true, dummy, true);
        }
    }
}
void AClass_Racer_Pawn::DriftLeft(float rotateSpeed)
{
    if(CanDrift()){
        // state = FLYING_WHILE_DRIFTING;
        entityPtr->SetState(FLYING_WHILE_DRIFTING);

        rotation.Yaw -= rotateSpeed;
        if(rotation.Roll >= -90)
            rotation.Roll -= 1 * rotateSpeed;
        FHitResult dummy;
//        rotation.Clamp();
        AActor::K2_SetActorRelativeRotation(rotation, true, dummy, true);
    }
}
void AClass_Racer_Pawn::DriftDown(float rotateSpeed)
{
    if(CanDrift()){
        // state = FLYING_WHILE_DRIFTING;
        entityPtr->SetState(FLYING_WHILE_DRIFTING);
    
//        if(rotation.Pitch >= -90){
        if(true){
            rotation.Pitch -= rotateSpeed;
            FHitResult dummy;
    //        rotation.Clamp();
            AActor::K2_SetActorRelativeRotation(rotation, true, dummy, true);
        }
    }
}
void AClass_Racer_Pawn::DriftRight(float rotateSpeed)
{
    if(CanDrift()){
        // state = FLYING_WHILE_DRIFTING;
        entityPtr->SetState(FLYING_WHILE_DRIFTING);
        
        rotation.Yaw += rotateSpeed;
        if(rotation.Roll <= 90)
            rotation.Roll += 1 * rotateSpeed;
        FHitResult dummy;
//        rotation.Clamp();
        AActor::K2_SetActorRelativeRotation(rotation, true, dummy, true);
    }
}

void AClass_Racer_Pawn::StopDrift(){
    if(entityPtr && entityPtr->GetState() == FLYING_WHILE_DRIFTING){ entityPtr->SetState(FLYING); }
}

void AClass_Racer_Pawn::SetState(TEnumAsByte<EntityState> newState){entityPtr->SetState(newState);}


void AClass_Racer_Pawn::StunFor(float duration)
{
    
}

void AClass_Racer_Pawn::RagdollFor(float duration){
    // state = RAGDOLLED;
    entityPtr->SetState(RAGDOLLED);

    if(skeletalMeshPtr){
        skeletalMeshPtr->SetPhysicsBlendWeight(1.0f);
        skeletalMeshPtr->SetAllBodiesSimulatePhysics(true);
    }
    else{ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for USkeletalMeshComponent for Class_Racer_Pawn is null, method cancelled"));}
}

void AClass_Racer_Pawn::UnRagdoll(){
    if(skeletalMeshPtr){
//        AActor::K2_SetActorLocationAndRotation(skeletalMeshPtr->GetComponentLocation())
        FHitResult dummy;
//        AActor::K2_SetActorLocation(skeletalMeshPtr->GetComponentLocation(), false, dummy, true);
        AActor::K2_SetActorLocation(skeletalMeshPtr->GetSkeletalCenterOfMass(), true, dummy, true);
        // skeletalMeshPtr->K2_SetRelativeLocation(FVector{0,0,0}, true, dummy, true);
        
        // state = FLYING;
        entityPtr->SetState(FLYING);

        DriftUp(1.0);
        skeletalMeshPtr->ResetAllBodiesSimulatePhysics();
        skeletalMeshPtr->SetPhysicsBlendWeight(0.1f);
        DriftUp(1.0);   // to fix glitch of torso and chest being separated
    }
    else{ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for USkeletalMeshComponent for Class_Racer_Pawn is null, method cancelled")); }
}

FString AClass_Racer_Pawn::GetSpeedIntAsString(){
    int speedInt = static_cast<int>(round( UKismetMathLibrary::VSize(GetVelocity()) ));
    FString temp = FString(TEXT("Speed: "));
    temp.AppendInt(speedInt);
    return temp;
}

FString AClass_Racer_Pawn::GetRootComponentSpeedIntAsString(){
    int speedInt = static_cast<int>(round( GetRootComponent()->GetComponentVelocity().Size() ));
    FString temp = FString(TEXT("Speed: "));
    temp.AppendInt(speedInt);
    return temp;
}

float AClass_Racer_Pawn::GetSpeedFloat(int decimalPlaces){ return 1.0; }
int AClass_Racer_Pawn::GetSpeedInt(){ return 1; }
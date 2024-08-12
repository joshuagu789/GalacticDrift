// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Racer_Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActorComponents/Class_DamageableActor.h"
using namespace std;

/*
 Expects all variables to be initialized in blueprint
 */
AClass_Racer_Pawn::AClass_Racer_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_Racer_Pawn::BeginPlay()
{
	Super::BeginPlay();

    if(!moveComponentPtr){
        moveComponentPtr = GetComponentByClass<UFloatingPawnMovement>();
        if(!moveComponentPtr){
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: moveComponentPtr is nullptr for Class_Racer_Pawn"));
        }
    }
    if(!skeletalMeshPtr){
        skeletalMeshPtr = GetComponentByClass<USkeletalMeshComponent>();
        if(!skeletalMeshPtr){
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: skeletalMeshPtr is nullptr for Class_Racer_Pawn"));
        }
    }
    if(!entityPtr){
        entityPtr = GetComponentByClass<UClass_Entity>();
        if(!entityPtr){
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entityPtr is nullptr for Class_Racer_Pawn"));
        }
    }
    if(!beaconPtr){
        beaconPtr = GetComponentByClass<UClass_Beacon>();
        if(!beaconPtr){
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: beaconPtr is nullptr for Class_Racer_Pawn"));
        }
    }
    StartFlying(0.7, true, 0.1);
}

// Called every frame
void AClass_Racer_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(entityPtr){
        // moveComponentPtr->AddInputVector(GetActorForwardVector() * speed, isAccelerating);
        if(moveComponentPtr && (entityPtr->GetState() == FLYING_WHILE_DRIFTING || entityPtr->GetState() == FLYING || entityPtr->GetState() == RAMMING ) ){
            moveComponentPtr->AddInputVector(GetActorForwardVector() * 2000, isAccelerating);
        }
        else if(moveComponentPtr){
            moveComponentPtr->StopMovementImmediately();
        }
        if(CanDrift() && entityPtr->GetState() != FLYING_WHILE_DRIFTING){
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
    // else if(moveComponentPtr){
    //     // moveComponentPtr->ConsumeInputVector();
    //     // moveComponentPtr->AddInputVector(GetActorLocation(), false);
    //     moveComponentPtr->StopMovementImmediately();
    //     // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I SHOULD VE LANDING AND NOT MOVING"));
    // }

    if(landTime > 0){
        FRotator targetRotation = GetActorRotation();
        targetRotation.Roll = 0;
        targetRotation.Pitch = 0;

        SetActorRotation(GetActorRotation() + (targetRotation-GetActorRotation()) * 6 * DeltaTime);
        SetActorLocation(GetActorLocation() + ((landLocation - GetActorLocation()) * 6 * DeltaTime));
        landTime -= DeltaTime;
    }
    if(takeOffTime > 0){
        takeOffTime -= DeltaTime;

        if(takeOffTime <= 0){
            entityPtr->SetState(FLYING);

            UClass_DamageableActor* damager = GetComponentByClass<UClass_DamageableActor>();
            UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(GetRootComponent());

            if(damager){
                damager->SetImmunityTime(5);
            }
            if(mesh){
                mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
                mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            }
        }
        // if(takeOffTime <= 0){
        //     if(mesh){
        //         // mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
        //         // mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        //     }
        // }
    }
}

// Called to bind functionality to input
void AClass_Racer_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AClass_Racer_Pawn::LandOn(AActor* actor, const FVector& worldLandLocation){
    if(entityPtr && actor && !isLanded && takeOffTime <= 0){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I SHOULD BE LANDING NOW"));

        UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(GetRootComponent());

        if(mesh){
    		mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
        }

        // AttachToActor();
        landLocation = worldLandLocation;
        entityPtr->SetState(LANDED);

        AttachToActor(actor, FAttachmentTransformRules{ EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld,  false});
        isLanded = true;
        landTime = 7;
    }
}
void AClass_Racer_Pawn::TakeOff(){
    if(landTime <= 0 && isLanded){
        // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I SHOULD BE TAKING OFF"));
        DetachFromActor(FDetachmentTransformRules{FAttachmentTransformRules{ EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative,  false}, false});
        isLanded = false;
        takeOffTime = 4;
    }
}
bool AClass_Racer_Pawn::GetIsLanded(){ return isLanded && takeOffTime<=0; }

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
        if(rotation.Roll >= -450)
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
        if(rotation.Roll <= 450)
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

const FString& AClass_Racer_Pawn::GetUserName(){ return username; }


void AClass_Racer_Pawn::StunFor(float duration)
{
    
}

// void AClass_Racer_Pawn::RagdollFor(float duration){
//     // state = RAGDOLLED;
//     entityPtr->SetState(RAGDOLLED);

//     if(skeletalMeshPtr){
//         skeletalMeshPtr->SetPhysicsBlendWeight(1.0f);
//         skeletalMeshPtr->SetAllBodiesSimulatePhysics(true);
//     }
//     else{ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for USkeletalMeshComponent for Class_Racer_Pawn is null, method cancelled"));}
// }

// void AClass_Racer_Pawn::UnRagdoll(){
//     if(skeletalMeshPtr){
// //        AActor::K2_SetActorLocationAndRotation(skeletalMeshPtr->GetComponentLocation())
//         FHitResult dummy;
// //        AActor::K2_SetActorLocation(skeletalMeshPtr->GetComponentLocation(), false, dummy, true);
//         AActor::K2_SetActorLocation(skeletalMeshPtr->GetSkeletalCenterOfMass(), true, dummy, true);
//         // skeletalMeshPtr->K2_SetRelativeLocation(FVector{0,0,0}, true, dummy, true);
        
//         // state = FLYING;
//         entityPtr->SetState(FLYING);

//         DriftUp(1.0);
//         skeletalMeshPtr->ResetAllBodiesSimulatePhysics();
//         skeletalMeshPtr->SetPhysicsBlendWeight(0.1f);
//         DriftUp(1.0);   // to fix glitch of torso and chest being separated
//     }
//     else{ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for USkeletalMeshComponent for Class_Racer_Pawn is null, method cancelled")); }
// }

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

void AClass_Racer_Pawn::CompleteObjective(int stage, float points){
    lastCompletedObjective = stage;
    popularity += points;
}
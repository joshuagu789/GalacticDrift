// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Cannon.h"

// UClass_Sensor::UClass_Sensor()
// {
// 	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// 	// off to improve performance if you don't need them.
// 	PrimaryComponentTick.bCanEverTick = true;

// 	// ...
// }


// // Called when the game starts
// void UClass_Sensor::BeginPlay()
// {
// 	Super::BeginPlay();

// 	// ...
	
// }

void UClass_Cannon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(isAttacking && attackTarget){
        if(cooldownTimer <= 0){
            
            FVector selfLocation = GetOwner()->GetRootComponent()->K2_GetComponentLocation();
            FVector targetLocation = attackTarget->GetRootComponent()->K2_GetComponentLocation();

            if(FVector::DistSquared(selfLocation, targetLocation) <= attackRange * attackRange){

                FRotator rotationToTarget = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetRootComponent()->K2_GetComponentLocation(), attackTarget->GetActorLocation());
                float angleToTargetSquared = (rotationToTarget - GetOwner()->GetRootComponent()->K2_GetComponentRotation()).Euler().SizeSquared();

                if(angleToTargetSquared <= angleToFire){

                    // Starting salvo of bullets
                    if(timeBetweenEachTurretTimer <= 0){
                        
                        if(bulletSpawnPoints.Num() > 0){

                            //Shooting bullet
                            FVector spawnLocation = Cast<USceneComponent>(bulletSpawnPoints[turretIndex])->K2_GetComponentLocation();
                            //fire
                        		
                                FTransform blankTransform;
			                    blankTransform.SetLocation(spawnLocation);	
                                FActorSpawnParameters spawnParams;

                    			AActor* bullet = GetWorld()->SpawnActor<AActor>(projectilePtr, blankTransform, spawnParams);
                                UPrimitiveComponent* bulletBody = Cast<UPrimitiveComponent>(bullet->GetRootComponent());

                                if(bulletBody){
                                    
                                    FRotator angleToTarget = UKismetMathLibrary::FindLookAtRotation(bulletBody->K2_GetComponentLocation(), targetLocation);
                            		FHitResult dummy;
                                    bulletBody->K2_SetWorldRotation(angleToTarget, false, dummy, true);

                                    FVector impulseVector = (targetLocation-selfLocation).GetSafeNormal() * projectileSpeed;
                                    bulletBody->AddImpulse(impulseVector, "", true);

                                } else {
                                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: bullet spawned does not have primitive component as root for class cannon"));	        
                                }

                            timeBetweenEachTurretTimer = timeBetweenEachTurret;
                            turretIndex++;

                            // Reset everything
                            if(turretIndex == bulletSpawnPoints.Num()){
                                turretIndex = 0;
                                cooldownTimer = cooldown;
                            }

                        } else {
                            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no spawn points for bullets in Class Cannon"));	        
                        }

                    } else {
                        timeBetweenEachTurretTimer -= DeltaTime;
                    }
                    // for(UClass_Empty* spawnLocation: bulletSpawnPoints){}

                }

            }
        } else {
            cooldownTimer -= DeltaTime;
        }
    }
}

void UClass_Cannon::BeginAttacking(AActor* actor){
    if(actor){
        isAttacking = true;
        attackTarget = actor;
    }
    else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor is nullptr in BeginAttacking parameter of Class Cannon"));	
    }
}	

void UClass_Cannon::StopAttacking(){
    isAttacking = false;
    attackTarget = nullptr;
}	

bool UClass_Cannon::IsAttacking(){ return isAttacking; }

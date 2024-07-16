// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Cannon.h"

// UClass_Sensor::UClass_Sensor()
// {
// 	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// 	// off to improve performance if you don't need them.
// 	PrimaryComponentTick.bCanEverTick = true;

// 	// ...
// }


// Called when the game starts
void UClass_Cannon::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UClass_Cannon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(isAttacking && attackTarget && !attackTarget->IsPendingKillPending()){
        if(cooldownTimer <= 0){
            
            FVector selfLocation = GetOwner()->GetRootComponent()->K2_GetComponentLocation();
            FVector targetLocation = attackTarget->GetRootComponent()->K2_GetComponentLocation();
            float distanceSquaredToTarget = FVector::DistSquared(selfLocation, targetLocation);
            
            if(distanceSquaredToTarget <= attackRange * attackRange){

                FRotator rotationToTarget = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetRootComponent()->K2_GetComponentLocation(), attackTarget->GetActorLocation());
                float angleToTargetSquared = (rotationToTarget - GetOwner()->GetRootComponent()->K2_GetComponentRotation()).Euler().SizeSquared();

                if(angleToTargetSquared <= angleToFire){

                    // Starting salvo of bullets
                    if(timeBetweenEachTurretTimer <= 0){
                        
                        if(bulletSpawnPoints.Num() > 0){

                            ShootAt(attackTarget, distanceSquaredToTarget);
                            // if(shootAtFuncPtr){
                            //     // this->*shootAtFuncPtr(attackTarget, distanceSquaredToTarget);
                            //     *shootAtFuncPtr(attackTarget, distanceSquaredToTarget);
                            // }
                            //Shooting bullet
                            // FVector spawnLocation = Cast<USceneComponent>(bulletSpawnPoints[turretIndex])->K2_GetComponentLocation();
                        		
                            // FTransform blankTransform;
                            // blankTransform.SetLocation(spawnLocation);	
                            // FActorSpawnParameters spawnParams;

                            // AActor* bullet = GetWorld()->SpawnActor<AActor>(projectilePtr, blankTransform, spawnParams);
                            // UPrimitiveComponent* bulletBody = Cast<UPrimitiveComponent>(bullet->GetRootComponent());

                            // if(bulletBody){
                            //     // predicted location is where target will be in x amount of time where x is time for projectile to travel distance between cannon and its max range
                            //     float inaccuracyValue = UKismetMathLibrary::RandomFloatInRange(1,1+accuracy);
                            //     // FVector predictedTargetLocation = targetLocation + ( attackTarget->GetRootComponent()->GetComponentVelocity() * (inaccuracyValue * attackRange)/(projectileSpeed));   //(distanceSquaredToTarget)/(projectileSpeed * projectileSpeed)
                            //     FVector predictedTargetLocation = targetLocation + ( attackTarget->GetRootComponent()->GetComponentVelocity() * (inaccuracyValue * distanceSquaredToTarget)/(projectileSpeed * projectileSpeed));   //(distanceSquaredToTarget)/(projectileSpeed * projectileSpeed)
                                
                            //     // float inaccuracyValue = 0.1 * (distanceSquaredToTarget - distanceSquaredToTarget * accuracy);
                            //     // FVector inaccuracyOffset{ UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue), UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue), UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue)};
                            //     // predictedTargetLocation += inaccuracyOffset;

                            //     FRotator angleToTarget = UKismetMathLibrary::FindLookAtRotation(bulletBody->K2_GetComponentLocation(), predictedTargetLocation);
                            //     FHitResult dummy;
                            //     bulletBody->K2_SetWorldRotation(angleToTarget, false, dummy, false);
                            //     // bulletBody->K2_SetRelativeRotation(angleToTarget, false, dummy, false);

                            //     FVector impulseVector = (predictedTargetLocation - bulletBody->K2_GetComponentLocation()).GetSafeNormal() * projectileSpeed;
                            //     bulletBody->AddImpulse(impulseVector, "", true);

                            // } else {
                            //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: bullet spawned does not have primitive component as root for class cannon"));	        
                            // }

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

void UClass_Cannon::ShootAt(AActor* target, float distanceSquaredToTarget = 0){
    if(distanceSquaredToTarget == 0){
        distanceSquaredToTarget = FVector::DistSquared( GetOwner()->GetRootComponent()->K2_GetComponentLocation(), attackTarget->GetRootComponent()->K2_GetComponentLocation() );
    }
    FVector spawnLocation = Cast<USceneComponent>(bulletSpawnPoints[turretIndex])->K2_GetComponentLocation();
        
    FTransform blankTransform;
    blankTransform.SetLocation(spawnLocation);	
    FActorSpawnParameters spawnParams;

    AActor* bullet = GetWorld()->SpawnActor<AActor>(projectilePtr, blankTransform, spawnParams);

    if(!bullet){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: bullet not spawned for class cannon"));	        
        return;
    }

    bullet->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    UPrimitiveComponent* bulletBody = Cast<UPrimitiveComponent>(bullet->GetRootComponent());

    if(bulletBody){
        // predicted location is where target will be in x amount of time where x is time for projectile to travel distance between cannon and its max range
        float inaccuracyValue = UKismetMathLibrary::RandomFloatInRange(1,1+accuracy);
        // FVector predictedTargetLocation = targetLocation + ( attackTarget->GetRootComponent()->GetComponentVelocity() * (inaccuracyValue * attackRange)/(projectileSpeed));   //(distanceSquaredToTarget)/(projectileSpeed * projectileSpeed)
        FVector predictedTargetLocation = attackTarget->GetRootComponent()->K2_GetComponentLocation() + ( attackTarget->GetRootComponent()->GetComponentVelocity() * (inaccuracyValue * distanceSquaredToTarget)/(projectileSpeed * projectileSpeed));   //(distanceSquaredToTarget)/(projectileSpeed * projectileSpeed)
        
        // float inaccuracyValue = 0.1 * (distanceSquaredToTarget - distanceSquaredToTarget * accuracy);
        // FVector inaccuracyOffset{ UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue), UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue), UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue)};
        // predictedTargetLocation += inaccuracyOffset;

        FRotator angleToTarget = UKismetMathLibrary::FindLookAtRotation(bulletBody->K2_GetComponentLocation(), predictedTargetLocation);
        FHitResult dummy;
        bulletBody->K2_SetWorldRotation(angleToTarget, false, dummy, false);
        // bulletBody->K2_SetRelativeRotation(angleToTarget, false, dummy, false);

        FVector impulseVector = (predictedTargetLocation - bulletBody->K2_GetComponentLocation()).GetSafeNormal() * projectileSpeed;
        bulletBody->AddImpulse(impulseVector, "", true);

    } else {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: bullet spawned does not have primitive component as root for class cannon"));	        
    }
}


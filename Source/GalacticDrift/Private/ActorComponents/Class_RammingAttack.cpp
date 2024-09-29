// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_RammingAttack.h"
#include "Header_Enumerations.h"
// Sets default values for this component's properties
UClass_RammingAttack::UClass_RammingAttack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	ramCollider = CreateDefaultSubobject<USphereComponent>("RammingCollider");
	ramCollider->InitSphereRadius(0);
}


// Called when the game starts
void UClass_RammingAttack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	attackDelayTimer = attackDelay;
	if(!skeletalMeshPtr){
		skeletalMeshPtr = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	}
	if(!skeletalMeshPtr){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: skeletalMeshPtr is nullptr in Class RammingAttack, actor has no skeletal mesh"));	
	}
	if(!entityPtr){
		entityPtr = GetOwner()->GetComponentByClass<UClass_Entity>();
	}
	if(!damageComponentPtr){
		damageComponentPtr = GetOwner()->GetComponentByClass<UClass_DamageableActor>();
	}
	// if(!entityPtr){
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: skeletalMeshPtr is nullptr in Class RammingAttack, actor has no skeletal mesh"));	
	// }
	if(ramCollider){

		FAttachmentTransformRules rules{EAttachmentRule::SnapToTarget, false};

		if(skeletalMeshPtr){
			ramCollider->AttachToComponent(skeletalMeshPtr, rules);
		}
		else{
			ramCollider->AttachToComponent(GetOwner()->GetRootComponent(), rules);	
		}
		ramCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ramCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

		ramCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		// ramCollider->SetNotifyRigidBodyCollision(true);
	}
}


// Called every frame
void UClass_RammingAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(immunityDurationTimer > 0){
		immunityDurationTimer -= DeltaTime;
		if(immunityDurationTimer <= 0){
			StopAttacking();
			if(skeletalMeshPtr){
				skeletalMeshPtr->SetAllMassScale(originalMassScale);
			}
			if(entityPtr){
				entityPtr->SetState(FLYING);
			}
			if(ramCollider){
				ramCollider->SetAllMassScale(originalMassScale);
				ramCollider->SetSphereRadius(0, true);
			}

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ramming over"));	
		}
	}
	if(cooldownTimer <= 0 && immunityDurationTimer <= 0){
		if(isAttacking){
			attackDelayTimer -= DeltaTime;

			if(attackDelayTimer <= 0){
				if(entityPtr && entityPtr->GetState() != RAGDOLLED || !entityPtr){
					if(skeletalMeshPtr){
						skeletalMeshPtr->SetAllMassScale(massMultiplier);
					}
					
					if(damageComponentPtr){
						damageComponentPtr->SetImmunityTime(immunityDuration);
					}
					if(entityPtr){
						entityPtr->SetState(RAMMING);
					}

					immunityDurationTimer = immunityDuration;
					attackDelayTimer = attackDelay;
					cooldownTimer+= cooldown;

					if(ramCollider){
						ramCollider->SetAllMassScale(massMultiplier);
						ramCollider->SetSphereRadius(collisionRange, true);
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ADJUSTING RADIUSW"));	
					}
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("RAMMING NOW"));	
				}
				else{
					attackDelayTimer = attackDelay;
					StopAttacking();
			        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("cancelling ram attack because ragdolled"));	

				}
			}
		}
	}
	else if(immunityDurationTimer <= 0){
		cooldownTimer -= DeltaTime;
	}
}

void UClass_RammingAttack::BeginAttacking(AActor* actor = nullptr){
    // if(actor){
    //     attackTarget = actor;
    // }
	if(cooldownTimer <= 0 && entityPtr && entityPtr->GetState() != RAGDOLLED || cooldownTimer <= 0 && !entityPtr){
		if(actor){
			attackTarget = actor;
		}
		isAttacking = true;
	}
}

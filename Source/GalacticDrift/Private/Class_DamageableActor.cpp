/*
	For three types of actors that can be damaged from collisions: ones that break apart on collision (asteroids), ones that destroy themselves
	and spawn broken parts on collision (robots for example), ones that ragdoll on collision (racers)
*/
// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_DamageableActor.h"

// Sets default values for this component's properties
UClass_DamageableActor::UClass_DamageableActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_DamageableActor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	actualHealth = health;
}


// Called every frame
void UClass_DamageableActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(ragdollTimer > 0 && type == RAGDOLLABLE){
		ragdollTimer -= DeltaTime;
		if(ragdollTimer <= 0){
			UnRagdoll();
		}
	}
	if(collisionTimer >= 0){
		collisionTimer -= DeltaTime;
	}
}

float UClass_DamageableActor::CalculateAndApplyDamage(UPrimitiveComponent* collisionSource){
	if(collisionTimer > 0){
		return 0;
	}
	collisionTimer += 0.05;	//Damaging collisions can only occur every 0.05 seconds
	float damage = GetOwner()->GetRootComponent()->GetComponentVelocity().SizeSquared();

	if(collisionSource){
		damage += collisionSource->GetComponentVelocity().SizeSquared();
	}
	if(damage < health/20){	//If damage too small to matter
		return 0;
	}
	damage = UKismetMathLibrary::Sqrt(damage);
	damage *= 0.2;
	actualHealth -= damage;
	mostRecentDamage = damage;
	return damage;
}

TEnumAsByte<DamageableActor_Type> UClass_DamageableActor::GetType(){ return type; }

bool UClass_DamageableActor::IsDestroyed(){ return actualHealth <= 0; }

void UClass_DamageableActor::ResetHealth(){ actualHealth = health; }

/*
Ragdoll and unragdoll used often for racers, need to check if owner of component is a racer as special case
*/
void UClass_DamageableActor::Ragdoll(){
	if(type != RAGDOLLABLE){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Ragdoll not intended for non RAGDOLLABLE of Class_DamageableActor"));
		return;
	}
	USkeletalMeshComponent* skeletalMeshPtr = Cast<USkeletalMeshComponent>(GetOwner()->GetRootComponent());
    if(skeletalMeshPtr){
		AClass_Racer_Pawn* racerPtr = Cast<AClass_Racer_Pawn>(GetOwner());
		if(racerPtr){
			racerPtr->SetState(RAGDOLLED);
		}
        skeletalMeshPtr->SetPhysicsBlendWeight(1.0f);
        skeletalMeshPtr->SetAllBodiesSimulatePhysics(true);
    }
    else{ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Actor with Class_DamageableActor component of type RAGDOLLABLE doesn't have skeletal mesh as root component"));}
	
	// if(mostRecentDamage/40.0 > maxRagdollTime)
	// 	return maxRagdollTime;
	// return mostRecentDamage/40.0; 
	// ragdollTimer = (mostRecentDamage/400 + maxRagdollTime > maxRagdollTime) ? (maxRagdollTime):(mostRecentDamage/400 + maxRagdollTime);
	ragdollTimer = (mostRecentDamage/40 > maxRagdollTime) ? (maxRagdollTime):(mostRecentDamage/40);
}

void UClass_DamageableActor::UnRagdoll(){
	if(type != RAGDOLLABLE){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Ragdoll not intended for non RAGDOLLABLE of Class_DamageableActor"));
		return;
	}
	USkeletalMeshComponent* skeletalMeshPtr = Cast<USkeletalMeshComponent>(GetOwner()->GetRootComponent());
    if(skeletalMeshPtr){
        FHitResult dummy;
        GetOwner()->K2_SetActorLocation(skeletalMeshPtr->GetSkeletalCenterOfMass(), true, dummy, true);
        
		AClass_Racer_Pawn* racerPtr = Cast<AClass_Racer_Pawn>(GetOwner());
		if(racerPtr){
			racerPtr->SetState(FLYING);
		}

		GetOwner()->K2_SetActorRelativeRotation( GetOwner()->GetTransform().Rotator(), true, dummy, true);
        skeletalMeshPtr->ResetAllBodiesSimulatePhysics();
        skeletalMeshPtr->SetPhysicsBlendWeight(0.1f);
        GetOwner()->K2_SetActorRelativeRotation( GetOwner()->GetTransform().Rotator(), true, dummy, true);   // to fix glitch of torso and chest being separated
    }
    else{ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Actor with Class_DamageableActor component of type RAGDOLLABLE doesn't have skeletal mesh as root component"));}	
}

// void UClass_DamageableActor::SelfDestruct(AActor* collisionSource){
// 	if(type != EXPLODABLE){
//         GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: SelfDestruct not intended for non EXPLODABLE of Class_DamageableActor"));
// 		return;
// 	}
// 	if(destroyedVersionPtr){
// 		FActorSpawnParameters spawnParams;
// 		// spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 		AActor* temp = GetWorld()->SpawnActor<AActor>(destroyedVersionPtr, GetOwner()->GetTransform(), spawnParams);
// 		// UGeometryCollectionComponent* collection = Cast<UGeometryCollectionComponent>(temp->GetRootComponent());

// 		UPrimitiveComponent* collection = Cast<UPrimitiveComponent>(temp->GetRootComponent());
// 		UMeshComponent* collection2 = Cast<UMeshComponent>(collection);
// 		// UGeometryCollectionComponent* collection3 = Cast<UGeometryCollectionComponent>(collection2);


// 		// UGeometryCollectionComponent* collection = temp->GetComponentByClass<UGeometryCollectionComponent>();
// 	}

// }



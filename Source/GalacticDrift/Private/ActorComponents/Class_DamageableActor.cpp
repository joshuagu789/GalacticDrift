/*
	For three types of actors that can be damaged from collisions: ones that break apart on collision (asteroids), ones that destroy themselves
	and spawn broken parts on collision (robots for example), ones that ragdoll on collision (racers)
*/
// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_DamageableActor.h"

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
	entityPtr = GetOwner()->GetComponentByClass<UClass_Entity>();
	immunityTimer = timeImmuneAfterSpawning;
	actualHealth = health;
	if(type == RAGDOLLABLE){
		skeletalMeshPtr = Cast<USkeletalMeshComponent>(GetOwner()->GetRootComponent());
		if(!skeletalMeshPtr){
    		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Actor of type RAGDOLLABLE has no skeleton as root component in Class_DamageableActor"));
		}
	}
	SetComponentTickInterval(0.1);
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
	else if(collisionTimer >= 0){
		collisionTimer -= DeltaTime;
	}
	else if(recoveringFromRagdoll){
		if(skeletalMeshPtr && ragdollBlendWeight > 0.1){
			ragdollBlendWeight -= DeltaTime;
			skeletalMeshPtr->SetPhysicsBlendWeight(ragdollBlendWeight);

	        FHitResult dummy;
			skeletonFixer.Pitch += DeltaTime;
			skeletonFixer.Roll += DeltaTime;
			skeletonFixer.Yaw += DeltaTime;
			GetOwner()->K2_SetActorRelativeRotation( skeletonFixer, true, dummy, true);
		}
		else{
        	FHitResult dummy;

			recoveringFromRagdoll = false;
        	skeletalMeshPtr->ResetAllBodiesSimulatePhysics();
			skeletalMeshPtr->SetPhysicsBlendWeight(0.1);
		}
	}
	if(immunityTimer > 0){ immunityTimer -= DeltaTime; }
}

float UClass_DamageableActor::CalculateAndApplyDamage(UPrimitiveComponent* collisionSource){

	UClass_Entity* collisionEntity = collisionSource->GetOwner()->FindComponentByClass<UClass_Entity>();
	if(collisionTimer > 0 || immunityTimer > 0 || collisionEntity && entityPtr && entityPtr->IsFriendlyWith(collisionEntity->GetType())){
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

void UClass_DamageableActor::SetImmunityTime(float duration){
	immunityTimer = duration;
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
    if(skeletalMeshPtr){
		// UClass_Entity* entityPtr = GetOwner()->FindComponentByClass<UClass_Entity>();
		if(entityPtr){
			entityPtr->SetState(RAGDOLLED);
		}
        skeletalMeshPtr->SetPhysicsBlendWeight(1.0f);
        skeletalMeshPtr->SetAllBodiesSimulatePhysics(true);
    }
    else{ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Actor with Class_DamageableActor component of type RAGDOLLABLE doesn't have skeletal mesh as root component"));}
	
	UPawnMovementComponent* pawnMovementPtr = GetOwner()->FindComponentByClass<UPawnMovementComponent>();
	if(pawnMovementPtr){
		pawnMovementPtr->ConsumeInputVector();
	}
	// if(mostRecentDamage/40.0 > maxRagdollTime)
	// 	return maxRagdollTime;
	// return mostRecentDamage/40.0; 
	// ragdollTimer = (mostRecentDamage/400 + maxRagdollTime > maxRagdollTime) ? (maxRagdollTime):(mostRecentDamage/400 + maxRagdollTime);
	recoveringFromRagdoll = false;
	ragdollTimer = (mostRecentDamage/40 > maxRagdollTime) ? (maxRagdollTime):(mostRecentDamage/40);
}

void UClass_DamageableActor::UnRagdoll(){
	if(type != RAGDOLLABLE){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Ragdoll not intended for non RAGDOLLABLE of Class_DamageableActor"));
		return;
	}
    if(skeletalMeshPtr){
        skeletalMeshPtr->SetAllBodiesSimulatePhysics(false);

        // skeletalMeshPtr->ResetAllBodiesSimulatePhysics();

        FHitResult dummy;
		FVector teleportLocation = skeletalMeshPtr->GetSkeletalCenterOfMass();
		skeletonFixer = GetOwner()->GetRootComponent()->GetComponentRotation();
		skeletonFixer.Pitch++;

        GetOwner()->K2_SetActorLocation(teleportLocation, false, dummy, true);

        // skeletalMeshPtr->ResetAllBodiesSimulatePhysics();

		// UClass_Entity* entityPtr = GetOwner()->FindComponentByClass<UClass_Entity>();
		if(entityPtr){
			entityPtr->SetState(FLYING);
		}

		GetOwner()->K2_SetActorRelativeRotation( skeletonFixer, true, dummy, true);

        // skeletalMeshPtr->ResetAllBodiesSimulatePhysics();
		ragdollBlendWeight = 0.5;
		recoveringFromRagdoll = true;

		skeletonFixer.Pitch++;
        GetOwner()->K2_SetActorRelativeRotation( skeletonFixer, true, dummy, true);   // to fix glitch of torso and chest being separated
        // GetOwner()->K2_SetActorLocation(teleportLocation, true, dummy, false);
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



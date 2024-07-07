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
	
}


// Called every frame
void UClass_DamageableActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UClass_DamageableActor::CalculateAndApplyDamage(UPrimitiveComponent* collisionSource){
	float damage = GetOwner()->GetRootComponent()->GetComponentVelocity().Size();
	if(collisionSource){
		damage += collisionSource->GetComponentVelocity().Size();
	}
	damage *= 0.1;
	health -= damage;
	return damage;
}

TEnumAsByte<DamageableActor_Type> UClass_DamageableActor::GetType(){ return type; }

bool UClass_DamageableActor::IsDestroyed(){ return health <= 0; }

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



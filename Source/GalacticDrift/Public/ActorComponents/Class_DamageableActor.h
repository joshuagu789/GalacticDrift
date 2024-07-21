// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
// #include "Engine/EngineTypes.h"	// spawn collision resolution enum
#include "Class_FracturedActor.h"
// #include "Components/ActorComponent.h"
#include "Class_Entity.h"
#include "Header_Enumerations.h"
#include "Class_DamageableActor.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_DamageableActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_DamageableActor();

	UFUNCTION(BlueprintCallable)
		float CalculateAndApplyDamage(UPrimitiveComponent* collisionSource);
	UFUNCTION(BlueprintCallable)
		TEnumAsByte<DamageableActor_Type> GetType();
	UFUNCTION(BlueprintCallable)
		bool IsDestroyed();
	UFUNCTION(BlueprintCallable)
		void ResetHealth();
	UFUNCTION(BlueprintCallable)
		void Ragdoll();
	UFUNCTION(BlueprintCallable)
		void UnRagdoll();
	// UFUNCTION(BlueprintCallable)
	// /*
	// 	intended for EXPLODABLE type only, destroys owner actor in process
	// */
	// 	[[deprecated]]
	// 	void SelfDestruct(AActor* collisionSource);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<DamageableActor_Type> type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float timeImmuneAfterSpawning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxRagdollTime = 4;	// for Ragdollable only
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AClass_FracturedActor> destroyedVersionPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass_Entity* entityPtr;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 	UGeometryCollectionComponent* geometryCollectionPtr;

	UPROPERTY()
		FRotator skeletonFixer;

	float actualHealth;
	float mostRecentDamage;
	float ragdollTimer;
	float collisionTimer;
	float immunityTimer;

	bool recoveringFromRagdoll;
	UPROPERTY()
		USkeletalMeshComponent* skeletalMeshPtr; 		// for ragdolls
	float ragdollBlendWeight;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

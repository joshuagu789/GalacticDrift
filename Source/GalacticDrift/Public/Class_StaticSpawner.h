// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Objective.h"
#include "Engine/StaticMesh.h"
#include "Class_StaticSpawner.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_StaticSpawner : public AClass_Objective
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_StaticSpawner();

	UFUNCTION()
        void SpawnStaticsRectangle(int amount, float max_x, float max_y, float max_z, float min_scale, float max_scale);

	bool BeginEvent() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* staticMeshPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> destroyedMeshPtr;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 	UStaticMeshComponent* staticMeshTemplate;
	// UPROPERTY()
	// 	UStaticMesh* actualMeshPtr;
	UPROPERTY()
		TMap<UStaticMeshComponent*, float> meshes;
	// UPROPERTY()
	// 	TSet<AActor*> destroyedMeshes;

	UPROPERTY()
		bool destroyable = false;

	bool hasSpawned = false;

	int amountLeftToSpawn = 0;
	int x = 0;
	int y = 0;
	int z = 0;
	int scale1 = 1;
	int scale2 = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// UFUNCTION()
	// void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
    //                   AActor* OtherActor, 
    //                   UPrimitiveComponent* OtherComp, 
    //                   int32 OtherBodyIndex, 
    //                   bool bFromSweep, 
    //                   const FHitResult &SweepResult );

	UFUNCTION()
	void EventHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& Hit);
	// void EventHit(UPrimitiveComponent* MyComp, 
    //                   AActor* OtherActor, 
    //                   UPrimitiveComponent* OtherComp, 
	// 				  bool selfMoved,
	// 				  FVector hitLocation,
	// 				  FVector hitNormal,
    //                   FVector normalImpulse, 
	// 				  const FHitResult& Hit);

	// UFUNCTION()
	// void ReceiveHit
	// (
	// 	class UPrimitiveComponent * MyComp,
	// 	AActor * Other,
	// 	class UPrimitiveComponent * OtherComp,
	// 	bool bSelfMoved,
	// 	FVector HitLocation,
	// 	FVector HitNormal,
	// 	FVector NormalImpulse,
	// 	const FHitResult & Hit
	// );
};

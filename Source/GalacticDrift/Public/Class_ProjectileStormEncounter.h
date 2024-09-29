// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Encounter.h"
#include "Class_ProjectileStormEncounter.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_ProjectileStormEncounter : public AClass_Encounter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_ProjectileStormEncounter();

	UFUNCTION()
		void SpawnProjectile();
	
	void EndEvent() override;
	bool BeginEvent() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*
		Must be above or equal to 0.25 (program will set to 0.25 if too low)
		*/
		float spawnInterval = 0.25;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 	TSubclassOf<AActor> projectilePtr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* projectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float projectileHealth = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> destroyedProjectilePtr;
	UPROPERTY()
		TMap<UStaticMeshComponent*, float> projectiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float projectileSpeed = 3000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*
		IN DEGREES
		*/
		float projectileRotationSpeed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		/*
		Negative lifetime means projectile has no expiration time
		*/
		float projectileLifetime = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float minScale = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxScale = 1;

	UPROPERTY()
		/*
		Is actually the OFFSET from center of actor
		*/
		FVector projectileOriginOffset = {0,0,0};
	UPROPERTY()
		FVector projectileDestination = {0,0,0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool applyPhysics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool applySpin;


private:
	// tracking lifetimes
	TQueue<UStaticMeshComponent*> projectileQueue;
	TQueue<float> timeQueue;
	// TQueue<AActor*> projectileQueue;
	// TQueue<float> timeQueue;
	// std::queue<float> test;

	int currentIndex = 0;
	float timePassed = 0;
	float spawnTimer = 0;
	bool hasSetProjectileOrigin = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void EventHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& Hit);

    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult ) override;
};

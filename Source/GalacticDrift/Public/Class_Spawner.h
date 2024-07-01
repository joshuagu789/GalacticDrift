// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Entity.h"
#include "Class_Spawner.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Spawner : public AClass_Entity
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_Spawner();

    UFUNCTION(BlueprintCallable, Category="Action")
		/*
			min and max for range of actors to spawn, max_x is furthest x distance from center, same pattern for max_y and max_z
		*/
        void SpawnActorsEllipse(int min, int max, float max_x, float max_y, float max_z, float min_scale, float max_scale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//Experimental data structure- reasoning is lots of deletion (possibly) and each actor is unique
		TSet<AActor*> actorList;	
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> actorPtr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

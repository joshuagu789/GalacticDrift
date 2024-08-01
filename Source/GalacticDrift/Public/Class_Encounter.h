// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Event.h"
#include "Class_Encounter.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Encounter : public AClass_Event
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_Encounter();

	// bool BeginEvent() override;
	void RevealToRacers(const TSet<AActor*>& racers) override;
	void EndEvent() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float duration = 60;
	UPROPERTY()
		TArray<AActor*> victims;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult ) override;
};

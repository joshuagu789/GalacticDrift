// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_RacingGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Header_Enumerations.h"
#include "Components/SphereComponent.h"
#include "Class_Event.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Event : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_Event();

	// UFUNCTION()
	// 	/*
	// 	Returns false if event already playing
	// 	*/
	// 	virtual bool BeginEvent();
	// UFUNCTION()
	// 	virtual void EndEvent();
	// UFUNCTION()
	// 	virtual bool RevealToRacers();	// typically through marker component
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPrimitiveComponent* eventStartDetection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool startEventOnBeginPlay = false;

	UPROPERTY()
		UClass_RacingGameInstance* server;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable )
    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult );

	void OnActorBeginOverlap(AActor* OtherActor);
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("u shall work!"));
// }

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Class_Swivel.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_Swivel : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Swivel();

	UFUNCTION(BlueprintCallable)
		void BeginFacing(AActor* actor);
	UFUNCTION(BlueprintCallable)
		void StopRotating();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		AActor* rotateTarget;
	bool isRotating;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

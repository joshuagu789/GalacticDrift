/*
	Blank components with transforms for tracking spawn points of bullets
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Class_Empty.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_Empty : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Empty();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

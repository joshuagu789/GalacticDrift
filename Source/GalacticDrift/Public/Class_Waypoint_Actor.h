// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Racer_Pawn.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Class_Waypoint_Widget.h"
#include "Class_Waypoint_Actor.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Waypoint_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_Waypoint_Actor();

	UFUNCTION()
		void ConfigureWaypoint(FText categoryText, FText titleText, AClass_Racer_Pawn* racerTarget);

	UFUNCTION()
		void UpdateWaypointText();
	UFUNCTION()
		void SetCategory(FText categoryText);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
		UClass_Waypoint_Widget* widgetPtr;
	UPROPERTY()
		UTextBlock* textPtr;
	UPROPERTY()
		AClass_Racer_Pawn* racer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText title;
	UPROPERTY()
		FText outputText;

	bool ready = false;
	float timer = 0.1;	// slight delay to allow widget to finish initializing text box ptr
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "Class_Equipment.h"
#include "Class_Marker.h"
#include "Header_Enumerations.h"
#include "Class_Sensor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALACTICDRIFT_API UClass_Sensor : public UClass_Equipment
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Sensor();

	void TakeDamage(float damage);
	void Repair(float amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Ability")
		TMap<TEnumAsByte<MarkerType>, FVector> ScanMarkers(const TSet<AActor*> &markers);	// for ai
	UFUNCTION(BlueprintCallable, Category="Ability")
		TArray<FString> ScanMarkersStrings(const TSet<AActor*> &markers);	// for player
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};

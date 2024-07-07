// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// #include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/ActorComponent.h"
#include "Header_Enumerations.h"
#include "Class_DamageableActor.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_DamageableActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_DamageableActor();

	UFUNCTION(BlueprintCallable)
		float CalculateAndApplyDamage();
	UFUNCTION(BlueprintCallable)
		TEnumAsByte<DamageableActor_Type> GetType();
	UFUNCTION(BlueprintCallable)
		bool IsDestroyed();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<DamageableActor_Type> type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float health;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 	UActorComponent* spawnOnDestroyPtr;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

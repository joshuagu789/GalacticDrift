/*
	Cannot create instances of UClass_Entity but rather the blueprint BP_Entity that implements this
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Header_Enumerations.h"
#include "Components/ActorComponent.h"

// #include "Class_RacingGameInstance.h"
#include "Class_RacingGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "Class_Entity.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_Entity : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Entity();

	UFUNCTION(BlueprintCallable)
		TArray<TEnumAsByte<EntityType>> GetEnemyTypes();
	UFUNCTION(BlueprintCallable)
		bool IsEnemyWith(TEnumAsByte<EntityType> otherEntity);
	UFUNCTION(BlueprintCallable)
		bool IsFriendlyWith(TEnumAsByte<EntityType> otherEntity);
	UFUNCTION(BlueprintCallable)
		TEnumAsByte<EntityState> GetState();
	UFUNCTION(BlueprintCallable)
		void SetState(TEnumAsByte<EntityState> newState);
	UFUNCTION(BlueprintCallable)
		TEnumAsByte<EntityType> GetType();

	UFUNCTION(BlueprintCallable)
		AClass_RacingGameMode* GetServer();
		
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AClass_RacingGameMode* server;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EntityType> type = EMPTY;
	UPROPERTY()
		TEnumAsByte<EntityState> state = DEFAULT;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

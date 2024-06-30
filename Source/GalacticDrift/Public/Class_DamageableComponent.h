/*
	Any component of actor that can take damage and be disabled, typically does not expect any component to be of this type but rather its children
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Class_DamageableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALACTICDRIFT_API UClass_DamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_DamageableComponent();

	UFUNCTION(BlueprintCallable, Category="Action")
		void TakeDamage(float damage);
	UFUNCTION(BlueprintCallable, Category="Action")
		void Repair(float amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		float health = 100;
	bool broken = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Class_Freezable.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Class_FreezableActor.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_FreezableActor : public UClass_Freezable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_FreezableActor();

	void Freeze() override;
	void UnFreeze() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool makeActorInvisibleOnFreeze = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool destroyRootComponentOnFreeze = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<USceneComponent> rootComponentCopy;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

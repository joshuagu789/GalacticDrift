// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Class_InGameHUD.h"
#include "Class_InGameWidget.h"
#include "Class_Racer_Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Class_PlayerUI.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_PlayerUI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_PlayerUI();

	UFUNCTION()
		void RelayMessageToConsole(FString message);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AClass_InGameHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass_InGameWidget* widget;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

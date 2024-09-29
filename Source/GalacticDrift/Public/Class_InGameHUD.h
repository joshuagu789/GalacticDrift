// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Class_InGameWidget.h"
#include "Class_InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GALACTICDRIFT_API AClass_InGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION()
		UClass_InGameWidget* GetWidget();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass_InGameWidget* widget;
};

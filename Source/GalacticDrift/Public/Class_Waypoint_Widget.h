// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Class_Waypoint_Widget.generated.h"

/**
 * 
 */
UCLASS()
class GALACTICDRIFT_API UClass_Waypoint_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
		UTextBlock* GetTextPtr();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* textPtr;
	// UPROPERTY()
	// 	FText name;
	// UPROPERTY()
	// 	FText name;
};

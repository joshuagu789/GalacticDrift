// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Containers/Array.h"
#include "Containers/Queue.h"
#include "Class_InGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class GALACTICDRIFT_API UClass_InGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* speedPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UTextBlock*> textBlocks;
	//queue for lines of text to print to screen ui
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> linesToPrint;	// Treat this like a queue
public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

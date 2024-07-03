// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
// #include "Internationalization/Text.h"
// #include "Containers/Array.h"
// #include "Containers/Queue.h"
#include "Header_Enumerations.h"
#include "Class_InGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class GALACTICDRIFT_API UClass_InGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="UI")
		void PushToOutputConsole(const TArray<FString> &lines);

protected:
	/*
	NOTE: ALL VARIABLES EXPECTED FOR BLUEPRINT TO INITIALIZE
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* speedPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UTextBlock*> textBlocks;	// EXPERIMENTAL: IS IT REALLY WORTH IT TO HAVE ALL TEXT BLOCKS IN ARRAY?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* outputConsolePtr;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<UI_Command_Menu> menuState = ALL_ABILITIES_MENU;

	/*
	everything below should be private but keep public for debugging
	*/
	TQueue<FString> linesToPrint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString line;

private:
	UFUNCTION()
		void UpdateOutputConsole(float InDeltaTime);
	float outputConsoleTimer = 0;
	int lineIndex = 0;
public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};

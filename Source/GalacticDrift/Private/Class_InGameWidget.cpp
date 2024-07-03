// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_InGameWidget.h"

void UClass_InGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    UpdateOutputConsole(InDeltaTime);
}

void UClass_InGameWidget::PushToOutputConsole(const TArray<FString> &lines){    
    for(auto i: lines)
        linesToPrint.Enqueue(i);
}

void UClass_InGameWidget::UpdateOutputConsole(float InDeltaTime){

    if(!line.IsEmpty()){
        // if(!linesToPrint.IsEmpty()){    // swap line 21 with 20

            if(outputConsoleTimer <= 0){
                if(outputConsolePtr){

                    FText temp = outputConsolePtr->GetText();
                    FText character = FText::FromString( line.Mid(lineIndex, 1) );

                    outputConsoleTimer += 0.05;
                    lineIndex++;

                    if(lineIndex > line.Len()){
                        character = FText::Join(character, FText::FromString(FString("\n")) );
	                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("adding new line character"));
                        line.Empty();
                    }
                    outputConsolePtr->SetText( FText::Join(NSLOCTEXT("a","b",""), temp, character) );

                } else {
	                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: outputConsolePtr null for Class_InGameWidget"));
                }
            } else {
                outputConsoleTimer -= InDeltaTime;
            }
        // }
    } else if(!linesToPrint.IsEmpty()){
        lineIndex = 0;
        outputConsoleTimer = 0;
        // FString temp = linesToPrint.Peek();
        // linesToPrint.Pop();
        // line = temp;

        FString temp;
        linesToPrint.Dequeue(temp);     // does dequeue store into temp???
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("dequeue called"));
        line = temp;
        // line = linesToPrint.Dequeue();
        // add next line to output
    }
}
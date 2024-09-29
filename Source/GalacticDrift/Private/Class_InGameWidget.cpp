// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_InGameWidget.h"

void UClass_InGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    UpdateOutputConsole(InDeltaTime);
}

void UClass_InGameWidget::NativeConstruct(){
    Super::NativeConstruct();

    if(beaconCanvasPtr){
        beaconCanvasPtr->SetVisibility(ESlateVisibility::Hidden);
    }
    if(allAbilitiesCanvasPtr){
        allAbilitiesCanvasPtr->SetVisibility(ESlateVisibility::Visible);
    }
    menuState = ALL_ABILITIES_MENU;
}

void UClass_InGameWidget::PushToOutputConsole(const TArray<FString> &lines){    
    for(auto i: lines)
        linesToPrint.Enqueue(i);
}

void UClass_InGameWidget::PushLineToOutputConsole(const FString& newLine){
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("received message in ingamewidget"));
    linesToPrint.Enqueue(newLine);
}

void UClass_InGameWidget::SwitchToMenu(TEnumAsByte<UI_Command_Menu> newMenuState){
    UCanvasPanel* oldCanvas = GetCanvasCorrespondingToEnum(menuState);
    if(oldCanvas){
        oldCanvas->SetVisibility(ESlateVisibility::Hidden);
    }
    UCanvasPanel* newCanvas = GetCanvasCorrespondingToEnum(newMenuState);
    if(newCanvas){
        newCanvas->SetVisibility(ESlateVisibility::Visible);
    }
    menuState = newMenuState;
}

UCanvasPanel* UClass_InGameWidget::GetCanvasCorrespondingToEnum(TEnumAsByte<UI_Command_Menu> menuEnum){
    switch(menuEnum){
        case ALL_ABILITIES_MENU:
            return allAbilitiesCanvasPtr;
        case BEACON_MENU:
            return beaconCanvasPtr;
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: returned allAbilitiesCanvasPtr bc nothing found in switch statement in class_ingamewidget"));
    return allAbilitiesCanvasPtr;
}

void UClass_InGameWidget::ProcessInputForMenu(FString input){

    if(input.Equals(TEXT("z")), ESearchCase::Type::IgnoreCase ){
        StepBackwardsInMenu();
    }
    else if(input.Equals(TEXT("3")), ESearchCase::Type::IgnoreCase ){
        if(menuState == ALL_ABILITIES_MENU){
            SwitchToMenu(BEACON_MENU);
        }   
    }
}

void UClass_InGameWidget::StepBackwardsInMenu(){
    switch(menuState){
        case BEACON_MENU:
            SwitchToMenu(ALL_ABILITIES_MENU);
            return;

    }
}

TEnumAsByte<UI_Command_Menu> UClass_InGameWidget::GetMenuState(){return menuState;}

void UClass_InGameWidget::MonitorPlayerEquipments(){}

void UClass_InGameWidget::UpdateOutputConsole(float InDeltaTime){

    if(!line.IsEmpty()){
        // if(!linesToPrint.IsEmpty()){    // swap line 21 with 20

            if(outputConsoleTimer <= 0){
                if(outputConsolePtr){

                    FText temp = outputConsolePtr->GetText();
                    FText character = FText::FromString( line.Mid(lineIndex, 1) );

                    // outputConsoleTimer += 0.005;
                    outputConsoleTimer = 0.005;
                    outputConsoleTextLifetimeTimer = 10.0;
                    lineIndex++;

                    if(lineIndex > line.Len()){
                        character = FText::Join(character, FText::FromString(FString("\n")) );
	                    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("adding new line character"));
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
        // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("dequeue called"));
        line = temp;
        // line = linesToPrint.Dequeue();
        // add next line to output
    }
    else{
        outputConsoleTextLifetimeTimer -= InDeltaTime;
        if(outputConsoleTextLifetimeTimer <= 0)
            outputConsolePtr->SetText( FText::FromString(FString("")) );
    }
}
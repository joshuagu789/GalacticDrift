// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_InGameHUD.h"

void AClass_InGameHUD::BeginPlay(){
	Super::BeginPlay();

    SetActorTickInterval(0.5);
    
    // LoadObjectivesOfStage(1);   
}

UClass_InGameWidget* AClass_InGameHUD::GetWidget(){ return widget; }

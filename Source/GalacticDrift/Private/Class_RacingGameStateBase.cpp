// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_RacingGameStateBase.h"

bool AClass_RacingGameStateBase::AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("server received?"));
	if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity tried to send empty actor pointer to game server"));
		return false;
	}
	if(type == MARKER){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("dont blow up on me now?!!??"));
        // markerList.Add(1);
        // markerList.Add(actor);
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("lets do this slowly"));
		// if(markerList.Contains(actor)){
        // 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity already added to game server"));
		// 	return false;
		// } else {
		// 	markerList.Add(actor);
	    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("success?!!??"));
        // }
	}
	return false;
}
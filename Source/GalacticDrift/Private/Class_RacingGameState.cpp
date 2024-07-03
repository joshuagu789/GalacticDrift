// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_RacingGameState.h"

bool AClass_RacingGameState::AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor){
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("server received?"));
	// if(!actor){
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity tried to send empty actor pointer to game server"));
	// 	return false;
	// }
	// if(type == MARKER){
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("asdasdas?!!??"));
    //     // markerList.Add(1);
    //     // test = test+1;
    //     // markerList.Add(actor);
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("qqq"));
	// 	// if(markerList.Contains(actor)){
    //     // 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity already added to game server"));
	// 	// 	return false;
	// 	// } else {
	// 	// 	markerList.Add(actor);
	//     //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("success?!!??"));
    //     // }
	// }
	return false;
}
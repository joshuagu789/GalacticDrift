// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_RacingGameInstance.h"

bool UClass_RacingGameInstance::AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor){
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("received on instance"));
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, UKismetTextLibrary::Conv_IntToText( UKismetMathLibrary::Conv_ByteToInt(type) ));
	if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity tried to send empty actor pointer to game server"));
		return false;
	}
    TSet<AActor*>* containerPtr = &ConvertEnumToContainer(type);
    if(containerPtr){
        if(containerPtr->Contains(actor)){
        	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity already added to game server"));
            delete containerPtr;
			return false;   
        } else {
			containerPtr->Add(actor);
	        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("success?!!??"));
            delete containerPtr;
            return true;
        }
    }
    delete containerPtr;
	// if(type == MARKER){
	// 	if(markerList.Contains(actor)){
    //     	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity already added to game server"));
	// 		return false;
	// 	} else {
	// 		markerList.Add(actor);
	//         GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("success?!!??"));
    //     }
	// }
	return false;
}

void UClass_RacingGameInstance::testprinting(){
    test = 5;
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("can anyone hear me?"));
}

TSet<AActor*>& UClass_RacingGameInstance::ConvertEnumToContainer(TEnumAsByte<EntityType> type)
{
    switch(type){
        case RACER:
            return racerList;
            break;
        case MARKER:
            return markerList;
            break;
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no valid conversion from entity enum to container in racing game instance"));
    return emptyList;
}
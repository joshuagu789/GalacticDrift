// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_RacingGameInstance.h"

bool UClass_RacingGameInstance::AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor){
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("received on instance"));

	if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity tried to send empty actor pointer to game server"));
		return false;
	}
    TSet<AActor*>* containerPtr = &GetContainerForEnum(type);
    if(containerPtr){
        if(containerPtr->Contains(actor)){
        	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity already added to game server"));
			return false;   
        } else {
			containerPtr->Add(actor);
            return true;
        }
    }
	return false;
}

TSet<AActor*>& UClass_RacingGameInstance::GetContainerForEnum(TEnumAsByte<EntityType> type)
{
    switch(type){
        case RACER:
            return racerList;
            break;
        case MARKER:
	        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("marker received"));
            return markerList;
            break;
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no valid conversion from entity enum to container in racing game instance"));
    return emptyList;
}
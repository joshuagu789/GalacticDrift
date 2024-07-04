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
        	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity already added to game server, overriding original actor"));
			containerPtr->Add(actor);
			return false;   
        } else {
			containerPtr->Add(actor);
            return true;
        }
    }
	return false;
}

bool UClass_RacingGameInstance::AddMarkerToServer(AActor* actor){
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("received on instance"));

	if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity tried to send empty actor pointer to game server"));
		return false;
	}
    if(markerList.Contains(actor)){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity already added to game server, overriding original actor"));
        markerList.Add(actor);
        return false;   
    } else {
        markerList.Add(actor);
        return true;
    }
    
	return false;
}

TSet<AActor*>& UClass_RacingGameInstance::GetContainerForEnum(const TEnumAsByte<EntityType> type)
{
    switch(type){
        case RACER:
            return racerList;
            break;
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no valid conversion from entity enum to container in racing game instance"));
    return emptyList;
}

TSet<AActor*>& UClass_RacingGameInstance::GetMarkers(){ return markerList; }

AActor* UClass_RacingGameInstance::GetClosestEntityTo(const TArray<TEnumAsByte<EntityType>> &entityTypes, const AActor* actor){

    AActor* currentClosest = nullptr;
    float currentClosestDistanceSquared;

    if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: passd in actor pointer is nullptr for GetClosestEntityTo in racing game instance, returning nullptr"));  
        return currentClosest;
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("getclosestentityto"));

    for(TEnumAsByte<EntityType> type: entityTypes){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("going through types"));

        TSet<AActor*>* containerPtr = &GetContainerForEnum(type);
        if(containerPtr){
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("containerPtr is not null"));

            for(AActor* entity: *containerPtr){
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("comparing racer"));
                if(!currentClosest){    // first entity always closest to prevent currentClosest from staying null
                    currentClosest = entity;
                    currentClosestDistanceSquared = actor->GetSquaredDistanceTo(currentClosest);
                } else if ( currentClosestDistanceSquared > actor->GetSquaredDistanceTo(entity) ){
                    currentClosest = entity;
                    currentClosestDistanceSquared = actor->GetSquaredDistanceTo(currentClosest);                    
                }
            }
        } else {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: containerPtr is nullptr for GetClosestEntityTo in racing game instance"));
        }
    }
    return currentClosest;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_RacingGameMode.h"

void AClass_RacingGameMode::BeginPlay(){
	Super::BeginPlay();

    SetActorTickInterval(0.5);

    if(objectives.Num() >= 1){
        FTransform blankTransform;
        blankTransform.SetLocation(FVector{20000,1240,1870});
        FActorSpawnParameters spawnParams;			

        AActor* temp = GetWorld()->SpawnActor<AActor>(objectives[0], blankTransform, spawnParams);
        if(temp){
            temp->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        }
    }
}

// Called every frame
void AClass_RacingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AClass_RacingGameMode::AddEntityToServer(TEnumAsByte<EntityType> type, AActor* actor){
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

bool AClass_RacingGameMode::RemoveEntityFromServer(TEnumAsByte<EntityType> type, AActor* actor){
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("received on instance"));

	if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity tried to send empty actor pointer to game server"));
		return false;
	}
    TSet<AActor*>* containerPtr = &GetContainerForEnum(type);
    if(containerPtr){
        if(!containerPtr->Contains(actor)){
        	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: entity not found in game server, overriding original actor"));
			// containerPtr->Add(actor);
			return false;   
        } else {
			containerPtr->Remove(actor);
            return true;
        }
    }

	return true;
}

bool AClass_RacingGameMode::AddMarkerToServer(AActor* actor){
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

TSet<AActor*>& AClass_RacingGameMode::GetContainerForEnum(const TEnumAsByte<EntityType> type)
{
    switch(type){
        case EMPTY:
            return emptyList;   
            break;
        case RACER:
            return racerList;
            break;
    }
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no valid conversion from entity enum to container in racing game instance"));
    return emptyList;
}

TSet<AActor*>& AClass_RacingGameMode::GetMarkers(){ return markerList; }

AActor* AClass_RacingGameMode::GetClosestEntityTo(const TArray<TEnumAsByte<EntityType>> &entityTypes, const AActor* actor){

    AActor* currentClosest = nullptr;
    float currentClosestDistanceSquared;

    if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: passd in actor pointer is nullptr for GetClosestEntityTo in racing game mode, returning nullptr"));  
        return currentClosest;
    }

    for(TEnumAsByte<EntityType> type: entityTypes){

        TSet<AActor*>* containerPtr = &GetContainerForEnum(type);
        if(containerPtr){

            for(auto &entity: *containerPtr){
                if(!currentClosest){    // first entity always closest to prevent currentClosest from staying null
                    currentClosest = entity;
                    currentClosestDistanceSquared = actor->GetSquaredDistanceTo(currentClosest);
                } else if ( currentClosestDistanceSquared > actor->GetSquaredDistanceTo(entity) ){
                    currentClosest = entity;
                    currentClosestDistanceSquared = actor->GetSquaredDistanceTo(currentClosest);                    
                }
            }
        } else {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: containerPtr is nullptr for GetClosestEntityTo in racing game mode"));
        }
    }
    return currentClosest;
}

AActor* AClass_RacingGameMode::GetClosestEntityToFOV(const TArray<TEnumAsByte<EntityType>> &entityTypes, const AActor* actor, const FVector& actorDirection, float angle, float range){

    AActor* currentClosest = nullptr;
    float currentClosestDistanceSquared;

    if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: passd in actor pointer is nullptr for GetClosestEntityTo in racing game mode, returning nullptr"));  
        return currentClosest;
    }

    for(TEnumAsByte<EntityType> type: entityTypes){

        TSet<AActor*>* containerPtr = &GetContainerForEnum(type);
        if(containerPtr){

            for(auto &entity: *containerPtr){
                if(!currentClosest){    // first entity always closest to prevent currentClosest from staying null
                    currentClosest = entity;
                    currentClosestDistanceSquared = actor->GetSquaredDistanceTo(currentClosest);
                
                // comparing cosines of angles (rather not take inverse cosine)
                } else if ( currentClosestDistanceSquared > actor->GetSquaredDistanceTo(entity) && entity->GetActorLocation().CosineAngle2D(actorDirection) <= UKismetMathLibrary::Cos(angle*3.14/180)){
                    currentClosest = entity;
                    currentClosestDistanceSquared = actor->GetSquaredDistanceTo(currentClosest);                    
                }
            }
        } else {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: containerPtr is nullptr for GetClosestEntityToFOV in racing game mode"));
        }
    }

    return currentClosest;
}

void AClass_RacingGameMode::BeginGame(){
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("beginning game in racing game mode"));
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Combatant.h"

// Sets default values
AClass_Combatant::AClass_Combatant()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_Combatant::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClass_Combatant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AClass_Combatant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AClass_Combatant::HasTarget(){ return target && !target->IsPendingKillPending(); }

bool AClass_Combatant::HasBackupTargets(){ return targetList.Num() >= 1 && targetList[0] && !targetList[0]->IsPendingKillPending(); }

bool AClass_Combatant::IsDespawning(){ return despawning; }

bool AClass_Combatant::AddTarget(AActor* actor){
	if(!actor){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor is null for AddTarget for Class_Combatant"));
		return false;
	}
	if(!targetList.Contains(actor)){
		if(!HasTarget()){
			target = actor;
		}
		else{
			// targetList.Insert(actor, 0);
			targetList.Add(actor);
		}
		return true;
	}
	return false;
}

void AClass_Combatant::RemoveTarget(AActor* actor){ targetList.Remove(actor); };


bool AClass_Combatant::CycleNextTarget(){
	if(targetList.Num() == 0 && HasTarget()){
		return true;
	}
	while(!HasTarget()){
		if(targetList.Num() >= 1){
			AActor* actor = targetList[0];
			if(actor){
				if(!actor->IsPendingKillPending()){
					target = actor;
					targetList.RemoveAt(0);
					return true;
				}
				targetList.RemoveAt(0);
			}
		}
		else{
			return false;
		}	
	}
	return false;
}

bool AClass_Combatant::HasActorInTargetList(AActor* actor){ return targetList.Contains(actor); }
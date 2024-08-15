// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_RacerAI.h"
#include "Class_Objective.h"

// Sets default values
AClass_RacerAI::AClass_RacerAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_RacerAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClass_RacerAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	decisionTimer -= DeltaTime;
	attackTimer -= DeltaTime;
	if(isAggressive){
		timeAggressive += DeltaTime;
	}
	if(entityPtr && (entityPtr->GetState() == FLYING_WHILE_DRIFTING || entityPtr->GetState() == FLYING)){
		if(!destination || destination->IsPendingKillPending()){
			AcquireDestination();
		}
		else{
			DriftTowardsDestination();
			if(isAggressive && attackTimer <= 0){
				attackTimer = 0.25;
				AttemptAttack();
			}
			if(decisionTimer <= 0){
				ToggleAggression();
				decisionTimer += 4;
			}
		}
	}
	else if(isLanded){
		// destination == nullptr;
		AcquireDestination();
		TakeOff();
	}
}

// Called to bind functionality to input
void AClass_RacerAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AClass_RacerAI::DriftTowardsDestination(){
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("drift called")); 
	if(!destination){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no destination")); 
		return;
	}
	if(destination->IsPendingKillPending()){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("nullptr")); 
		destination = nullptr;
		return;
	}
	FVector location = destination->GetActorLocation();
	FRotator rotationToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), location) - GetActorRotation();
	// SetActorRotation(rotationToTarget);
	float pitch = rotationToTarget.Pitch;
	float yaw = rotationToTarget.Yaw;
	float roll = rotationToTarget.Roll;

	pitch = (pitch < 0) ? (-1 * pitch) : (pitch);
	yaw = (yaw < 0) ? (-1 * yaw) : (yaw);
	roll = (roll < 0) ? (-1 * roll) : (roll);

	if(pitch + yaw + roll > 40){
		if(rotationToTarget.Pitch > 0){
			DriftUp(4.0);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("up")); 
		}
		else{
			DriftDown(4.0);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("down")); 
		}
		if(rotationToTarget.Yaw > 0){
			DriftRight(4.0);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("right")); 
		}
		else{
			DriftLeft(4.0);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("left")); 
		}
	}

	// if(pitch > yaw && pitch > roll){	// pitch case
	// 	if(rotationToTarget.Pitch > 0){
	// 		DriftUp();
	// 	}
	// 	else{
	// 		DriftDown();
	// 	}
	// }
	// else if(yaw > pitch && yaw > roll){		//yaw case

	// }
	// else{		// roll case

	// }

}

bool AClass_RacerAI::AcquireDestination(){
				// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("trying to find destination")); 
	if(entityPtr){
		AClass_RacingGameMode* server = entityPtr->GetServer();
		if(server){
			TSet<AActor*> objectives = server->GetObjectives();

			float minDistance = 1000000000;
			AActor* minActor;
			bool isFirst = true;

			for(AActor* actor: objectives){
				AClass_Objective* objective = Cast<AClass_Objective>(actor);
				if(objective && objective->GetStageNumber() > lastCompletedObjective){

					float distance = (objective->GetActorLocation() - GetActorLocation()).SizeSquared();
					if(distance < minDistance || isFirst){
						isFirst = false;
						minDistance = distance;
						minActor = actor;
					}
				}
			}
			if(minActor){
				destination = minActor;
				// if(moveComponentPtr){
				// 	moveComponentPtr->AddInputVector(destination->GetActorLocation() - GetActorLocation(), isAccelerating);
				// }
				// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("destination set")); 

				return true;
			}
		}
		// entityPtr->
	}
	return false;
}

void AClass_RacerAI::ToggleAggression(){


	if(timeAggressive > 5){
		if(!destination){
			isAggressive = false;
			timeAggressive = 0;
			AcquireDestination();
		}
		isAggressive = false;
		timeAggressive = 0;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("u not even worth the time!! heh")); 
		AcquireDestination();
		return;

		// PROBLEM WITH BELOW CODE IS COMPARING "ANGLE" TO DESTINATION THAT WAS ORIGINALLY OBJECTIVE BUT NOW SET TO PLAYER
		// FRotator rotationToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), destination->GetActorLocation()) - GetActorRotation();
		// if(rotationToTarget.Pitch + rotationToTarget.Yaw + rotationToTarget.Roll > 90){
		// 	isAggressive = false;
		// 	timeAggressive = 0;
		// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("u not even worth the time!! heh")); 
		// 	AcquireDestination();
		// 	return;
		// }
	}

	AClass_RacingGameMode* server = entityPtr->GetServer();

	AActor* farthestRacer;

	if(beaconPtr && server && beaconPtr->CanSpawnAttacker()){
		TSet<AActor*> racers = server->GetContainerForEnum(RACER);
		float maxDistance = -1000000000;
		bool isFirst = true;

		for(AActor* racer: racers){
			//AClass_Objective* objective = Cast<AClass_Objective>(actor);
			AClass_Racer_Pawn* racerClass = Cast<AClass_Racer_Pawn>(racer);
			if(racerClass && !racerClass->IsPendingKillPending() && !racerClass->GetIsLanded() && racer != this){

				float distance = racer->GetActorLocation().X;
				if(distance > maxDistance || isFirst){
					isFirst = false;
					maxDistance = distance;
					farthestRacer = racer;
				}
			}
		}
		 
		if(farthestRacer){
			//destination = minActor;
			//beaconPtr->SpawnAttacker(farthestRacer);
			//destination = farthestRacer;
			//return true;
		}
	}

	if(isAggressive){
		return;
	}

	AActor* closestRacerToFOV = server->GetClosestEntityToFOV(TArray<TEnumAsByte<EntityType>>{RACER}, this, GetActorForwardVector(), 40, 35000);
	if(closestRacerToFOV){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("RUNNNN RUNNN U R IN MY WAYY!!!")); 
		destination = closestRacerToFOV;
		isAggressive = true;
		timeAggressive = 0;
	}
}

void AClass_RacerAI::AttemptAttack(){
	if(!destination || !meleeAttackPtr || destination->IsPendingKillPending()){
		return;
	}
	float speedDifferenceSquared = (GetVelocity()-destination->GetVelocity()).SizeSquared();
	if(speedDifferenceSquared <= 1 && speedDifferenceSquared >= -1){ return; }	// avoid dividing by zero
	float distanceDifferenceSquared = ( GetActorLocation()-destination->GetActorLocation() ).SizeSquared();

	if(distanceDifferenceSquared / speedDifferenceSquared <= 3){
		meleeAttackPtr->BeginAttacking(destination);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I RAM YOU HAHA")); 
	}
	
}
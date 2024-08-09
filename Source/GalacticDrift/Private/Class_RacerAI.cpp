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

	if(!destination){
		AcquireDestination();
	}
	else{
		DriftTowards(destination->GetActorLocation());
	}
}

// Called to bind functionality to input
void AClass_RacerAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AClass_RacerAI::DriftTowards(FVector location){
	FRotator rotationToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), location) - GetActorRotation();
	// SetActorRotation(rotationToTarget);
	float pitch = rotationToTarget.Pitch;
	float yaw = rotationToTarget.Yaw;
	float roll = rotationToTarget.Roll;

	pitch = (pitch < 0) ? (-1 * pitch) : (pitch);
	yaw = (yaw < 0) ? (-1 * yaw) : (yaw);
	roll = (roll < 0) ? (-1 * roll) : (roll);

	if(pitch + yaw + roll > 30){
		if(rotationToTarget.Pitch > 0){
			DriftUp(4.0);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("up")); 
		}
		else{
			DriftDown(4.0);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("down")); 
		}
		if(rotationToTarget.Yaw > 0){
			DriftRight(4.0);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("right")); 
		}
		else{
			DriftLeft(4.0);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("left")); 
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
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("destination set")); 

				return true;
			}
		}
		// entityPtr->
	}
	return false;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_AdoringFan.h"

// Sets default values
AClass_AdoringFan::AClass_AdoringFan()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_AdoringFan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClass_AdoringFan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AClass_AdoringFan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AClass_AdoringFan::SetRacer(AClass_Racer_Pawn* newRacer){
	if(newRacer){
		racer = newRacer;
	}
	else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: newRacer is null for SetRacer for Class_AdoringFan"));
	}
}

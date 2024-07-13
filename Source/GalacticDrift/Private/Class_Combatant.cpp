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

bool AClass_Combatant::IsDespawning(){ return despawning; }

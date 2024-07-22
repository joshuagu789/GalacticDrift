// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Event.h"

// Sets default values
AClass_Event::AClass_Event()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_Event::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClass_Event::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_FracturedActor.h"

// Sets default values
AClass_FracturedActor::AClass_FracturedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_FracturedActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(1);
}

// Called every frame
void AClass_FracturedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	lifeTime -= DeltaTime;
	if(lifeTime <= 0 && !IsPendingKillPending()){
		K2_DestroyActor();
	}
}


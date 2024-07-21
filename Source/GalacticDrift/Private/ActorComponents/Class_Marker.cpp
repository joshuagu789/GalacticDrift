// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_Marker.h"

// Sets default values for this component's properties
UClass_Marker::UClass_Marker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Marker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_Marker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UClass_Marker::SetType(MarkerType newType){
	type = newType;
	return true;
}

FString UClass_Marker::GetMarkerName(){ return markerName; }


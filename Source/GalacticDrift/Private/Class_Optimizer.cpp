// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Optimizer.h"

// Sets default values for this component's properties
UClass_Optimizer::UClass_Optimizer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Optimizer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(collider){
		collider->OnComponentBeginOverlap.AddDynamic(this, &UClass_Optimizer::OnOverlapBegin);
	}
}


// Called every frame
void UClass_Optimizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClass_Optimizer::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									bool bFromSweep, const FHitResult& SweepResult){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OVERLLAPPINGGG"));
	// Super::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
}
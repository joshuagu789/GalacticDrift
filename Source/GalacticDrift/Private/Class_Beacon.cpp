// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Beacon.h"

// Sets default values for this component's properties
UClass_Beacon::UClass_Beacon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Beacon::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_Beacon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClass_Beacon::SpawnFan(){
    FTransform blankTransform;
	FVector spawnLocationOffset{UKismetMathLibrary::RandomFloatInRange(2000,4000 + 50000 - 50000 * accuracy),0,0};
	FRotator offsetRotation{UKismetMathLibrary::RandomFloatInRange(-30,30),UKismetMathLibrary::RandomFloatInRange(-30,30), UKismetMathLibrary::RandomFloatInRange(0,360)};
	spawnLocationOffset = offsetRotation.RotateVector(spawnLocationOffset);

    blankTransform.SetLocation(GetOwner()->GetRootComponent()->GetComponentLocation() + spawnLocationOffset);	

    FActorSpawnParameters spawnParams;
	// AClass_AdoringFan* fan = Cast<AClass_AdoringFan>(fanPtr);

    AActor* fan = GetWorld()->SpawnActor<AActor>(fanPtr, blankTransform, spawnParams);

	if(!fan){  
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: fan not spawned (nullptr) for SpawnFan of Class_Beacon"));
		return;
	}

	fan->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AClass_AdoringFan* fanClass = Cast<AClass_AdoringFan>(fan);

	if(!fanClass){  
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: spawned fan is not AClass_AdoringFan (nullptr) for SpawnFan of Class_Beacon"));
		return;
	}

	fanClass->SetRacer(Cast<AClass_Racer_Pawn>(GetOwner()));
	fanClass->SpawnDefaultController();
}
void UClass_Beacon::SpawnPolice(){

}
void UClass_Beacon::SpawnAttacker(AActor* target){

}

bool UClass_Beacon::CanSpawnFan(){ return fanTimer <= 0; }
bool UClass_Beacon::CanSpawnPolice(){ return policeTimer <= 0; }
bool UClass_Beacon::CanSpawnAttacker(){ return attackerTimer <= 0; }

float UClass_Beacon::GetFanCooldown(){ return fanTimer; }
float UClass_Beacon::GetPoliceCooldown(){ return policeTimer; }
float UClass_Beacon::GetAttackerCooldown(){ return attackerTimer; }

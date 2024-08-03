// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Encounter.h"

// Sets default values
AClass_Encounter::AClass_Encounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_Encounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClass_Encounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// bool AClass_Encounter::BeginEvent(){
// 	return Super::BeginEvent();
// }

void AClass_Encounter::RevealToRacers(const TSet<AActor*>& racers){
	Super::RevealToRacers(racers);

	for(auto& x: activeWaypoints){
		x.Value->SetCategory(FText::FromString("ENCOUNTER"));
	}
	// if(currentWaypointActor){
	// 	currentWaypointActor->SetCategory(FText::FromString("OBJECTIVE"));
	// }

}

void AClass_Encounter::BeginOverlap
(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult &SweepResult 
)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	AClass_Racer_Pawn* racer = Cast<AClass_Racer_Pawn>(OtherActor);
	if(racer && !victims.Contains(OtherActor)){
		victims.Add(OtherActor);
	}
}
bool AClass_Encounter::BeginEvent(){
	if(Super::BeginEvent()){
		server->BroadcastToPlayerConsoles(FString("Warning all Racers: ") + waypointTitle.ToString() + FString(" discovered, proceed with caution"));
		return true;
	}
	return false;
}
void AClass_Encounter::EndEvent(){
	AClass_Event::EndEvent();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("end asteroid storm event in encounter class"));
	// if(!IsPendingKillPending()){
	// 	K2_DestroyActor();
	// }
	// if(eventCollider){
	// 	eventCollider->SetGenerateOverlapEvents(false);
	// }else{
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no eventCollider in encounter???"));
	// }
}

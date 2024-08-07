// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_UpgradeStation.h"
#include "ActorComponents/Class_Equipment.h"
#include "ActorComponents/Class_PlayerUI.h"

// Sets default values
AClass_UpgradeStation::AClass_UpgradeStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_UpgradeStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClass_UpgradeStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClass_UpgradeStation::RewardRacer(AClass_Racer_Pawn* racer){
	AClass_Rewarder::RewardRacer(racer);
	if(racer){
		TInlineComponentArray<UClass_Equipment*, 10> components;	// reserve 10 for now
		racer->GetComponents<UClass_Equipment>(components, true);

		for(UClass_Equipment* equipment: components){
			if(equipment){
				equipment->FullRepair();
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("repair"));
			}
		}
		UClass_PlayerUI* playerUI = racer->GetComponentByClass<UClass_PlayerUI>();
		if(playerUI){
			playerUI->RelayMessageToConsole(FString("Equipment fully repaired"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Equipment fully repaired in class upgrade station"));

		}
		racer->LandOn(this, GetActorLocation()+FVector{0,0,370});
	}
}

void AClass_UpgradeStation::RevealToRacers(const TSet<AActor*>& racers){
	Super::RevealToRacers(racers);

	for(auto& x: activeWaypoints){
		x.Value->SetCategory(FText::FromString("UPGRADE"));
	}
}

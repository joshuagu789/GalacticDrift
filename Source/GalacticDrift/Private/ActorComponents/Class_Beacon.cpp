// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_Beacon.h"
#include "Class_Racer_Pawn.h"
#include "Class_AdoringFan.h"
#include "Class_Combatant.h"
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
	if(fanTimer > 0){
		fanTimer -= DeltaTime;
	}
	if(policeTimer > 0){
		policeTimer -= DeltaTime;
	}
	if(attackerTimer > 0){
		attackerTimer -= DeltaTime;
	}
}

void UClass_Beacon::SpawnFan(){
	if(!CanSpawnFan()){
		return;
	}
    FTransform blankTransform;
	FVector spawnLocationOffset{UKismetMathLibrary::RandomFloatInRange(5000,10000 + 50000 - 50000 * accuracy),0,0};
	FRotator offsetRotation{UKismetMathLibrary::RandomFloatInRange(-30,30),UKismetMathLibrary::RandomFloatInRange(-30,30), UKismetMathLibrary::RandomFloatInRange(0,360)};
	spawnLocationOffset = offsetRotation.RotateVector(spawnLocationOffset);

    blankTransform.SetLocation(GetOwner()->GetRootComponent()->GetComponentLocation() + GetOwner()->GetVelocity() * 3 + spawnLocationOffset);	

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
	fanTimer = fanCooldown;
}
void UClass_Beacon::SpawnPolice(){
	if(!CanSpawnPolice()){
		return;
	}
    FTransform blankTransform;
	FVector spawnLocationOffset{UKismetMathLibrary::RandomFloatInRange(5000,10000 + 50000 - 50000 * accuracy),0,0};
	FRotator offsetRotation{UKismetMathLibrary::RandomFloatInRange(-30,30),UKismetMathLibrary::RandomFloatInRange(-30,30), UKismetMathLibrary::RandomFloatInRange(0,360)};
	spawnLocationOffset = offsetRotation.RotateVector(spawnLocationOffset);

    blankTransform.SetLocation(GetOwner()->GetRootComponent()->GetComponentLocation() + GetOwner()->GetVelocity() * 3 + spawnLocationOffset);	

    FActorSpawnParameters spawnParams;
	// AClass_AdoringFan* fan = Cast<AClass_AdoringFan>(fanPtr);

    AActor* police = GetWorld()->SpawnActor<AActor>(policePtr, blankTransform, spawnParams);

	if(!police){  
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: police not spawned (nullptr) for SpawnPolice of Class_Beacon"));
		return;
	}

	police->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AClass_Combatant* combatantClass = Cast<AClass_Combatant>(police);

	if(!combatantClass){  
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: spawned police is not combatant (nullptr) for SpawnAttacker of Class_Beacon"));
		return;
	}
	
	combatantClass->SpawnDefaultController();

	UClass_OrbitMovement* orbitMovement = police->FindComponentByClass<UClass_OrbitMovement>();
	UClass_Swivel* swivel = police->FindComponentByClass<UClass_Swivel>();
	
	if(orbitMovement){
		orbitMovement->BeginOrbiting(GetOwner());
	}
	if(swivel){
		swivel->BeginFacing(GetOwner());
	}

	policeTimer = policeCooldown;
}
void UClass_Beacon::SpawnAttacker(AActor* target){
	if(!CanSpawnAttacker() || !target || target->IsPendingKillPending()){
		return;
	}

    FTransform blankTransform;
	FVector spawnLocationOffset{UKismetMathLibrary::RandomFloatInRange(5000,10000 + 50000 - 50000 * accuracy),0,0};
	FRotator offsetRotation{UKismetMathLibrary::RandomFloatInRange(-30,30),UKismetMathLibrary::RandomFloatInRange(-30,30), UKismetMathLibrary::RandomFloatInRange(0,360)};
	spawnLocationOffset = offsetRotation.RotateVector(spawnLocationOffset);

	if(!target){
	    blankTransform.SetLocation(GetOwner()->GetRootComponent()->GetComponentLocation() + GetOwner()->GetVelocity() * 3 + spawnLocationOffset);	
	}
	else if(target && !target->IsPendingKillPending()){
		FVector targetLocation = target->GetActorLocation();
		FVector targetVelocity = target->GetVelocity();
		blankTransform.SetLocation(targetLocation + targetVelocity * 3 + spawnLocationOffset);	
	}

    FActorSpawnParameters spawnParams;
	// AClass_AdoringFan* fan = Cast<AClass_AdoringFan>(fanPtr);

    AActor* attacker = GetWorld()->SpawnActor<AActor>(attackerPtr, blankTransform, spawnParams);

	if(!attacker){  
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: attacker not spawned (nullptr) for SpawnAttacker of Class_Beacon"));
		return;
	}

	attacker->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AClass_Combatant* combatantClass = Cast<AClass_Combatant>(attacker);

	if(!combatantClass){  
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: spawned attacker is not combatant (nullptr) for SpawnAttacker of Class_Beacon"));
		return;
	}

	// fanClass->SetRacer(Cast<AClass_Racer_Pawn>(GetOwner()));

	combatantClass->SpawnDefaultController();
	attackerTimer = attackerCooldown;
}

bool UClass_Beacon::CanSpawnFan(){ return fanTimer <= 0; }
bool UClass_Beacon::CanSpawnPolice(){ return policeTimer <= 0; }
bool UClass_Beacon::CanSpawnAttacker(){ return attackerTimer <= 0; }

float UClass_Beacon::GetFanCooldown(){ return fanTimer; }
float UClass_Beacon::GetPoliceCooldown(){ return policeTimer; }
float UClass_Beacon::GetAttackerCooldown(){ return attackerTimer; }

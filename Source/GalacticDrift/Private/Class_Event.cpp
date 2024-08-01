// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Event.h"

// Sets default values
AClass_Event::AClass_Event()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	eventCollider = CreateDefaultSubobject<USphereComponent>("EventStartDetection");
	eventCollider->SetLineThickness(10.f);
	eventCollider->InitSphereRadius(detectionRange);

	eventCollider->SetGenerateOverlapEvents(true);
	eventCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	eventCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	
	eventCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	eventCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);


	eventCollider->OnComponentBeginOverlap.AddDynamic( this, &AClass_Event::BeginOverlap );
	// OnActorBeginOverlap.AddDynamic( this, &AClass_Event::ActorBeginOverlap );	//notify? receive?
}

// Called when the game starts or when spawned
void AClass_Event::BeginPlay()
{
	Super::BeginPlay();
	// SetActorTickInterval(0.5);
	// OnActorBeginOverlap.AddDynamic( this, &AClass_Event::ActorBeginOverlap );	//notify? receive?

	eventCollider->SetSphereRadius(detectionRange, false);
	server = Cast<AClass_RacingGameMode>(UGameplayStatics::GetGameMode(this));
	if(server){
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("success"));
		// server->AddEntityToServer(RACER, this);
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Class_Event cant find game instance???"));
	}

}

// Called every frame
void AClass_Event::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClass_Event::BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult ){

	if(!eventActive){
		AClass_Racer_Pawn* racer = Cast<AClass_Racer_Pawn>(OtherActor);
		// if(racer && (racer->GetActorLocation() - GetActorLocation()).SizeSquared() <= detectionRange * detectionRange){
		// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("racer in event range"));
		// }
		if(racer && !eventActive){
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("starting event for racer"));
			BeginEvent();
			TSet<AActor*> temp;
			temp.Add(OtherActor);
			RevealToRacers(temp);
		}
	}

	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SOEMATHING OVERLAP MEEEE"));
}

bool AClass_Event::BeginEvent(){
	if(eventActive){
		return false;
	}
	eventActive = true;
	return true;
}
void AClass_Event::EndEvent(){
	eventActive = false;
	for(auto& pair: activeWaypoints){
		pair.Value->K2_DestroyActor();
		
	}
	activeWaypoints.Empty();

}
// void AClass_Event::RevealToRacers(AClass_Racer_Pawn* racer){	// should get racers from server?
void AClass_Event::RevealToRacers(const TSet<AActor*>& racers){	// should get racers from server?
	if(isRevealed){
		return;
	}
	// AActor* temp = Cast<AActor>(waypoint);
	// if()
	if(!waypoint){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: waypoint for Class Event is nullptr, returning"));
		return;
	}

	for(AActor* racer: racers){
		AClass_Racer_Pawn* tempRacer = Cast<AClass_Racer_Pawn>(racer);
		if(!tempRacer){
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor isn't class racer pawn in RevealToRacers in Class Event"));
			return;
		}
		UClass_PlayerUI* playerUI = tempRacer->FindComponentByClass<UClass_PlayerUI>();

		if(playerUI && !activeWaypoints.Contains(tempRacer)){
			FTransform blankTransform;
			blankTransform.SetLocation(GetActorLocation());
			FActorSpawnParameters spawnParams;			

			AActor* temp = GetWorld()->SpawnActor<AActor>(waypoint, blankTransform, spawnParams);
			if(temp){
				temp->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				temp->AttachToActor(this, FAttachmentTransformRules{EAttachmentRule::SnapToTarget, false});
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("create waypoint for event"));

				AClass_Waypoint_Actor* currentWaypointActor = Cast<AClass_Waypoint_Actor>(temp);
				if(!currentWaypointActor){
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: spawned waypoint for Class Event is not of type Class Waypoint Actor"));
					temp->K2_DestroyActor();
				}
				else{
					currentWaypointActor->ConfigureWaypoint(FText::FromString("EVENT"), waypointTitle, tempRacer);
					activeWaypoints.Add(tempRacer, currentWaypointActor);
				}
			}
		}
	}

	isRevealed = true;
}	

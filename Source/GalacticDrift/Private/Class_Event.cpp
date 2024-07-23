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
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("starting event for racer"));
			BeginEvent();
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SOEMATHING OVERLAP MEEEE"));
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
}
bool AClass_Event::RevealToRacers(){
	if(isRevealed){
		return false;
	}
	isRevealed = true;
	return true;
}	

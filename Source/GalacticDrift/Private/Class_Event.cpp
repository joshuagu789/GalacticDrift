// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Event.h"

// Sets default values
AClass_Event::AClass_Event()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	eventCollider = CreateDefaultSubobject<USphereComponent>("EventStartDetection");
	eventCollider->SetLineThickness(10.f);
	eventCollider->InitSphereRadius(1000.f);
	eventCollider->OnComponentBeginOverlap.AddDynamic( this, &AClass_Event::BeginOverlap );
	OnActorBeginOverlap.AddDynamic( this, &AClass_Event::ActorBeginOverlap );	//notify? receive?
}

// Called when the game starts or when spawned
void AClass_Event::BeginPlay()
{
	Super::BeginPlay();
	// OnActorBeginOverlap.AddDynamic( this, &AClass_Event::ActorBeginOverlap );	//notify? receive?

	server = Cast<UClass_RacingGameInstance>(UGameplayStatics::GetGameInstance(this));
	if(server){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("success"));
		server->AddEntityToServer(RACER, this);
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SOEMATHING OVERLAP MEEEE"));
}

void AClass_Event::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SOEMATHING OVERLAP MEEEE ACTOR"));
}

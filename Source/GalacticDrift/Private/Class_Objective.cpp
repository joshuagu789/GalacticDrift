// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Objective.h"

// Sets default values
AClass_Objective::AClass_Objective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rewardCollider = CreateDefaultSubobject<USphereComponent>("RewardDetection");
	// rewardCollider = NewNamedObject<USphereComponent>(this, "RewardDetection");

		// FAttachmentTransformRules rules{EAttachmentRule::SnapToTarget, false};
		// rewardCollider->AttachToComponent(GetRootComponent(), rules);
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("attach reward to event"));

	rewardCollider->InitSphereRadius(1000.f);
	rewardCollider->SetLineThickness(10.f);
	rewardCollider->SetGenerateOverlapEvents(true);
	rewardCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	rewardCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	rewardCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	rewardCollider->OnComponentBeginOverlap.AddDynamic( this, &AClass_Objective::RewardBeginOverlap );
	// this->OnActorBeginOverlap.AddDynamic( this, &AClass_Event::ActorBeginOverlap );	//notify? receive?
}

// Called when the game starts or when spawned
void AClass_Objective::BeginPlay()
{
	Super::BeginPlay();

	FAttachmentTransformRules rules{EAttachmentRule::SnapToTarget, false};
	rewardCollider->AttachToComponent(GetRootComponent(), rules);
}

// Called every frame
void AClass_Objective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// if(eventCollider){
	// 	FAttachmentTransformRules rules{EAttachmentRule::SnapToTarget, false};
	// 	rewardCollider->AttachToComponent(eventCollider, rules);
	// }
}

void AClass_Objective::RewardBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult ){
	// Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// USphereComponent* collider = Cast<USphereComponent>(OverlappedComponent);
	UPrimitiveComponent* test1 = Cast<UPrimitiveComponent>(eventCollider);
	UPrimitiveComponent* test2 = Cast<UPrimitiveComponent>(rewardCollider);

	if(OverlappedComponent && test1 && OverlappedComponent == test1){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("event collider hit"));
	}
	else if(OverlappedComponent && test2 && OverlappedComponent == test2){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("reward collider hit"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SOEMATHING OVERLAP MEEEE 3"));

}

// void AClass_Objective::ActorBeginOverlapReward(AActor* OverlappedActor, AActor* OtherActor){
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SOEMATHING OVERLAP MEEEE actor reward"));

// }
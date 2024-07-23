// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Objective.h"

// Sets default values
AClass_Objective::AClass_Objective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// rewardCollider = CreateDefaultSubobject<USphereComponent>("RewardDetection");
	// // rewardCollider = NewNamedObject<USphereComponent>(this, "RewardDetection");

	// 	// FAttachmentTransformRules rules{EAttachmentRule::SnapToTarget, false};
	// 	// rewardCollider->AttachToComponent(GetRootComponent(), rules);
	// 	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("attach reward to event"));

	// rewardCollider->InitSphereRadius(1000.f);
	// rewardCollider->SetLineThickness(10.f);
	// rewardCollider->SetGenerateOverlapEvents(true);
	// rewardCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// rewardCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	// rewardCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// rewardCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	// rewardCollider->OnComponentBeginOverlap.AddDynamic( this, &AClass_Objective::RewardBeginOverlap );
	// // this->OnActorBeginOverlap.AddDynamic( this, &AClass_Event::ActorBeginOverlap );	//notify? receive?
}

// Called when the game starts or when spawned
void AClass_Objective::BeginPlay()
{
	Super::BeginPlay();

	// FAttachmentTransformRules rules{EAttachmentRule::SnapToTarget, false};
	// rewardCollider->AttachToComponent(GetRootComponent(), rules);
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

bool AClass_Objective::BeginEvent(){
	return Super::BeginEvent();
}
void AClass_Objective::EndEvent(){
	Super::EndEvent();
}
bool AClass_Objective::RevealToRacers(){
	return Super::RevealToRacers();
}
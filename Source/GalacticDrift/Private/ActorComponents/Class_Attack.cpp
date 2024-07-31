// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_Attack.h"

// Sets default values for this component's properties
UClass_Attack::UClass_Attack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Attack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_Attack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClass_Attack::BeginAttacking(AActor* actor){
    if(actor){
        isAttacking = true;
        attackTarget = actor;
    }
    else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: actor is nullptr in BeginAttacking parameter of Class Attack"));	
    }
}

void UClass_Attack::StopAttacking(){
    isAttacking = false;
    attackTarget = nullptr;
}

bool UClass_Attack::IsAttacking(){ return isAttacking; }
// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_StaticSpawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AClass_StaticSpawner::AClass_StaticSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_StaticSpawner::BeginPlay()
{
	Super::BeginPlay();

	if(!staticMeshPtr){
		staticMeshPtr = GetComponentByClass<UStaticMeshComponent>();
	}
	if(!staticMeshPtr){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no static mesh found for static spawner"));
	}
}

// Called every frame
void AClass_StaticSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(amountLeftToSpawn > 0){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SPAWNING WAVE"));
		int amount = (amountLeftToSpawn >= 1000) ? (1000) : (amountLeftToSpawn);
		amountLeftToSpawn -= amount;
		SpawnStaticsRectangle(amount, x, y, z, scale1, scale2);
	}
	FHitResult* dummy = nullptr;
	GetRootComponent()->AddWorldRotation(FRotator{0,12 * DeltaTime,0}, true, dummy, ETeleportType::TeleportPhysics);
}

void AClass_StaticSpawner::SpawnStaticsRectangle(int amount, float max_x, float max_y, float max_z, float min_scale, float max_scale){
	if(staticMeshPtr){
		// int count = UKismetMathLibrary::RandomIntegerInRange(min,max);
		for(int i = 0; i < amount; i++){
			// FVector location = GetTransform().GetLocation();	// hopefully copies FVector not reference
			FVector location;

			location.X = UKismetMathLibrary::RandomFloatInRange(-max_x,max_x);
			location.Y = UKismetMathLibrary::RandomFloatInRange(-max_y,max_y);
			location.Z = UKismetMathLibrary::RandomFloatInRange(-max_z,max_z);

			FRotator rotation{UKismetMathLibrary::RandomFloatInRange(0,360),UKismetMathLibrary::RandomFloatInRange(0,360),UKismetMathLibrary::RandomFloatInRange(0,360)};
			
			float scale = UKismetMathLibrary::RandomFloatInRange(min_scale,max_scale);
			FVector scaleVector{scale,scale,scale}; 

			FTransform blankTransform;

			blankTransform.SetLocation(location);	//blankTransform is relative here 
			blankTransform.SetRotation(rotation.Quaternion());
			blankTransform.SetScale3D(scaleVector);
			//plan to also have random rotation and scale

       		FActorSpawnParameters spawnParams;			

				
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("attempting to spawn"));

			UStaticMeshComponent* temp = DuplicateObject <UStaticMeshComponent> (staticMeshPtr, this);
			if(temp){
				temp->SetStaticMesh(staticMeshPtr->GetStaticMesh());
				FinishAddComponent(Cast<UActorComponent>(temp), false, blankTransform);
				// temp->SetHiddenInGame(true,true);
				meshes.Add(temp, 100);
				// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("successfully spawned"));
			}
			FHitResult* dummy = nullptr;
			FHitResult dummyy;
			// temp->K2_SetWorldTransform(blankTransform, false, dummy, ETeleportType::ResetPhysics);
			// temp->K2_SetWorldTransform(blankTransform, false, dummyy, false);
			// temp->SetRelativeTransform(blankTransform, false, dummy, ETeleportType::None);
		}
	}
    else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for staticMeshPtr is null for Class StaticSpawner, method cancelled"));
    }
}


bool AClass_StaticSpawner::BeginEvent(){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("begin static asteroid field event"));

	if(Super::BeginEvent() && !hasSpawned){


		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("begin spawning for static asteroid field event"));


		amountLeftToSpawn = UKismetMathLibrary::RandomIntegerInRange(2500,2500);
		x = 55000;
		y = 55000;
		z = 55000;
		scale1 = 10;
		scale2 = 30;

		// SpawnActorsEllipse(10000,10000,60000,60000, 60000,10,35);
		hasSpawned = true;
		return true;
	}
	return false;
}

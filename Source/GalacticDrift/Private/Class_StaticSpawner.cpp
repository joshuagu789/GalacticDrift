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
	staticMesh = FindComponentByClass<UStaticMeshComponent>();
	if(!staticMesh){
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no static mesh found for static spawner"));
	}
	
}

// Called every frame
void AClass_StaticSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(amountLeftToSpawn > 0){
		int amount = (amountLeftToSpawn >= 50) ? (50) : (amountLeftToSpawn);
		amountLeftToSpawn -= amount;
		SpawnStaticsRectangle(amount, x, y, z, scale1, scale2);
	}
}

void AClass_StaticSpawner::SpawnStaticsRectangle(int amount, float max_x, float max_y, float max_z, float min_scale, float max_scale){
	if(staticMesh){
		// int count = UKismetMathLibrary::RandomIntegerInRange(min,max);
		for(int i = 0; i < amount; i++){
			FVector location = GetTransform().GetLocation();	// hopefully copies FVector not reference

			location.X += UKismetMathLibrary::RandomFloatInRange(-max_x,max_x);
			location.Y += UKismetMathLibrary::RandomFloatInRange(-max_y,max_y);
			location.Z += UKismetMathLibrary::RandomFloatInRange(-max_z,max_z);

			FRotator rotation{UKismetMathLibrary::RandomFloatInRange(0,360),UKismetMathLibrary::RandomFloatInRange(0,360),UKismetMathLibrary::RandomFloatInRange(0,360)};
			
			float scale = UKismetMathLibrary::RandomFloatInRange(min_scale,max_scale);
			FVector scaleVector{scale,scale,scale}; 

			FTransform blankTransform;
			blankTransform.SetLocation(location);
			blankTransform.SetRotation(rotation.Quaternion());
			blankTransform.SetScale3D(scaleVector);
			//plan to also have random rotation and scale

       		FActorSpawnParameters spawnParams;			

			UStaticMeshComponent* temp = DuplicateObject <UStaticMeshComponent> (staticMesh, this);
			FHitResult* dummy = nullptr;
			temp->SetWorldTransform(blankTransform, false, dummy, ETeleportType::None);

			// AActor* temp = GetWorld()->SpawnActor<AActor>(actorPtr, blankTransform, spawnParams);
			// if(temp){
			// 	temp->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			// 	temp->GetRootComponent()->SetWorldScale3D(FVector{scale, scale, scale});
			// 	//setactorscaleworld3d
			// }
		}
	}
    else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for staticmesh is null for Class StaticSpawner, method cancelled"));
    }
}


bool AClass_StaticSpawner::BeginEvent(){
	if(Super::BeginEvent() && !hasSpawned){

		amountLeftToSpawn = UKismetMathLibrary::RandomIntegerInRange(100,100);
		x = 5000;
		y = 5000;
		z = 5000;
		scale1 = 5;
		scale2 = 10;

		// SpawnActorsEllipse(10000,10000,60000,60000, 60000,10,35);
		hasSpawned = true;
		return true;
	}
	return false;
}

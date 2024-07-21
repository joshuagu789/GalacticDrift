// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Spawner.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AClass_Spawner::AClass_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_Spawner::BeginPlay()
{
	Super::BeginPlay();
	// SetActorTickInterval(0.5);
}

// Called every frame
void AClass_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult* dummy = nullptr;
	// GetRootComponent()->AddWorldRotation(FRotator{0,1 * DeltaTime,0}, true, dummy, ETeleportType::TeleportPhysics);

}

void AClass_Spawner::SpawnActorsEllipse(int min, int max, float max_x, float max_y, float max_z, float min_scale, float max_scale)
{
	if(actorPtr){
		int count = UKismetMathLibrary::RandomIntegerInRange(min,max);
		for(int i = 0; i < count; i++){
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

			AActor* temp = GetWorld()->SpawnActor<AActor>(actorPtr, blankTransform, spawnParams);
			if(temp){
				temp->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				temp->GetRootComponent()->SetWorldScale3D(FVector{scale, scale, scale});
				//setactorscaleworld3d

				UClass_RevolvingObject* revolvingObject = temp->FindComponentByClass<UClass_RevolvingObject>();

				// temp->GetRootComponent()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules{ EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative,  true});
				
				// if(revolvingObject){
				// 	revolvingObject->SetRevolveTarget(this, 0, 0, 7.5);;
				// }


				// APawn* pawn = Cast<APawn>(temp);
				// if(pawn){
				// 	pawn->SpawnDefaultController();
				// }


				actorList.Add(temp);
			}
		}
	}
    else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Pointer for subclass of AActor is null for Class_SpawnerAsteroid, method cancelled"));
    }
}

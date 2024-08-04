// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_StaticSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Class_FracturedActor.h"

// Sets default values
AClass_StaticSpawner::AClass_StaticSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// staticMeshTemplate = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshTemplate");

	// staticMeshTemplate->SetGenerateOverlapEvents(true);

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
	else{

		// FAttachmentTransformRules rules{EAttachmentRule::SnapToTarget, false};
		// staticMeshTemplate->AttachToComponent(GetRootComponent(), rules);

		// staticMeshTemplate->SetStaticMesh(staticMeshPtr->GetStaticMesh());
		// staticMeshTemplate->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		// staticMeshTemplate->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

		// staticMeshTemplate->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		// staticMeshTemplate->SetNotifyRigidBodyCollision(true);

		// staticMeshTemplate->SetRelativeScale3D(FVector{5,5,5});
		// staticMeshTemplate->OnComponentHit.AddDynamic(this, &AClass_StaticSpawner::EventHit);

		staticMeshPtr->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		staticMeshPtr->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

		staticMeshPtr->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		staticMeshPtr->SetNotifyRigidBodyCollision(true);

		staticMeshPtr->OnComponentHit.AddDynamic(this, &AClass_StaticSpawner::EventHit);
		// staticMeshPtr->SetRelativeScale3D(FVector{0,0,0});

		// staticMeshTemplate->OnComponentBeginOverlap.AddDynamic( this, &AClass_StaticSpawner::BeginOverlap );

	}
	// BeginEvent();
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
	// FHitResult* dummy = nullptr;
	// GetRootComponent()->AddWorldRotation(FRotator{0,12 * DeltaTime,0}, true, dummy, ETeleportType::TeleportPhysics);
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
				// temp->OnComponentHit.AddDynamic(this, &AClass_StaticSpawner::EventHit);

				// temp->SetHiddenInGame(true,true);
				meshes.Add(temp, 10);
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

	if(Super::BeginEvent() && !hasSpawned){

		amountLeftToSpawn = UKismetMathLibrary::RandomIntegerInRange(2000,2000);
		x = 55000;
		y = 55000;
		z = 55000;
		scale1 = 10;
		scale2 = 30;
		// amountLeftToSpawn = UKismetMathLibrary::RandomIntegerInRange(10,10);
		// x = 10000;
		// y = 10000;
		// z = 10000;
		// scale1 = 10;
		// scale2 = 20;

		// SpawnActorsEllipse(10000,10000,60000,60000, 60000,10,35);
		hasSpawned = true;
		return true;
	}
	return false;
}

void AClass_StaticSpawner::EventHit
(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	FVector normalImpulse, 
	const FHitResult& Hit
)
{
	AClass_FracturedActor* isFractured = Cast<AClass_FracturedActor>(OtherActor);
	// if(OtherActor != this && !isFractured && !destroyedMeshes.Contains(OtherActor)){
	if(OtherActor != this && !isFractured){
		UStaticMeshComponent* myComp = Cast<UStaticMeshComponent>(HitComponent);

		if(myComp && meshes.Contains(myComp)){
			meshes[myComp] -= 10;
			if(meshes[myComp] <= 0){
				FVector a = HitComponent->K2_GetComponentToWorld().GetScale3D();

				FTransform blankTransform;
				blankTransform.SetLocation(HitComponent->GetComponentTransform().GetLocation());
				blankTransform.SetRotation(HitComponent->GetComponentTransform().GetRotation());
				blankTransform.SetScale3D(a);

				FActorSpawnParameters spawnParams;			
				// FTransform{myComp->GetComponentQuat(), myComp->GetComponentLocation(), myComp->GetComponentScale()}
				UE_LOG(LogTemp, Warning, TEXT("The x value is: %f"), a.X);
				UE_LOG(LogTemp, Warning, TEXT("The y value is: %f"), a.Y);
				UE_LOG(LogTemp, Warning, TEXT("The z value is: %f"), a.Z);
				// AActor* temp = GetWorld()->SpawnActor<AActor>(destroyedMeshPtr, myComp->GetRelativeTransform(), spawnParams);
				AActor* temp = GetWorld()->SpawnActor<AActor>(destroyedMeshPtr, myComp->GetComponentTransform(), spawnParams);
				// USceneComponent* omg = Cast<USceneComponent>(HitComponent);
				// if(omg){
				// 	AActor* temp = GetWorld()->SpawnActor<AActor>(destroyedMeshPtr, omg->K2_GetComponentToWorld(), spawnParams);
		  		// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("somg"));
				// }
				// AActor* temp = GetWorld()->SpawnActor<AActor>(destroyedMeshPtr, HitComponent->K2_GetComponentToWorld(), spawnParams);
				// AActor* temp = GetWorld()->SpawnActor<AActor>(destroyedMeshPtr, blankTransform, spawnParams);
				if(temp){
					temp->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					// temp->GetRootComponent()->SetWorldScale3D(FVector{a.X, a.X, a.X});
					temp->GetRootComponent()->SetWorldScale3D(myComp->GetComponentTransform().GetScale3D());

					// UGeometryCollectionComponent* collection = Cast<UGeometryCollectionComponent>(temp->GetRootComponent());
					// UPrimitiveComponent* temp2 = Cast<UPrimitiveComponent>(temp->GetRootComponent());
					// temp->SetActorScale3D(a);
					// UGeometryCollectionComponent* collection;
					// collection = Cast<UGeometryCollectionComponent>(temp2);
					// if(!collection){
					// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: destroyed version doesnt have geometry collection as root component for class static spawner"));
					// }
					// else{
					// 	// collection->CrumbleActiveClusters();
					// }
				}
				myComp->DestroyComponent(true);
				meshes.Remove(myComp);
			}
		}
	}
					  
}

// void AClass_StaticSpawner::BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
// 					AActor* OtherActor, 
// 					UPrimitiveComponent* OtherComp, 
// 					int32 OtherBodyIndex, 
// 					bool bFromSweep, 
// 					const FHitResult &SweepResult )
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("static event overlap called"));
// }

// void AClass_StaticSpawner::EventHit
// (
// 	UPrimitiveComponent* MyComp, 
// 	AActor* OtherActor, 
// 	UPrimitiveComponent* OtherComp, 
// 	bool selfMoved,
// 	FVector hitLocation,
// 	FVector hitNormal,
// 	FVector normalImpulse, 
// 	const FHitResult& Hit
// )
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("event hit called"));
					  
// }

// void AClass_StaticSpawner::ReceiveHit
// (
// 	class UPrimitiveComponent * MyComp,
// 	AActor * Other,
// 	class UPrimitiveComponent * OtherComp,
// 	bool bSelfMoved,
// 	FVector HitLocation,
// 	FVector HitNormal,
// 	FVector NormalImpulse,
// 	const FHitResult & Hit
// ){
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("event hit called"));
// }
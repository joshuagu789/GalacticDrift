// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_ProjectileStormEncounter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Class_LifetimeComponent.h"

// Sets default values
AClass_ProjectileStormEncounter::AClass_ProjectileStormEncounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_ProjectileStormEncounter::BeginPlay()
{
	Super::BeginPlay();
	spawnInterval = (spawnInterval > 0.25) ? (spawnInterval) : (0.25);
	SetActorTickInterval(spawnInterval);
}

// Called every frame
void AClass_ProjectileStormEncounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(eventActive){
		duration -= DeltaTime;

		if(duration > 0){
			SpawnProjectile();
		}
		else{
			EndEvent();
		}
	}
	if(timeQueue.IsEmpty() && projectileQueue.IsEmpty()){
		timePassed = 0;
	}
	else if(!timeQueue.IsEmpty() && !projectileQueue.IsEmpty()){
		float* mostRecent = timeQueue.Peek();
		(*mostRecent) -= DeltaTime;

		timePassed += DeltaTime;

		if(*mostRecent <= 0){
			AActor* actor = *projectileQueue.Peek();
			if(actor){
				actor->K2_DestroyActor();
			}
			else{
        		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Couldnt get actor ptr off queue peek in Class ProjectileStormEncounter?"));
			}
			projectileQueue.Pop();
			timeQueue.Pop();

			if(!timeQueue.IsEmpty()){
				float* nextRecent = timeQueue.Peek();
				(*nextRecent) -= timePassed;
			}
		}
	}
	else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: timeQueue and projectileQueue not same size in Class ProjectileStormEncounter?"));
	}
}

void AClass_ProjectileStormEncounter::BeginOverlap
(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult &SweepResult 
)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	AClass_Racer_Pawn* racer = Cast<AClass_Racer_Pawn>(OtherActor);
	if(racer && !hasSetProjectileOrigin){
		projectileOriginOffset = GetActorLocation() - racer->GetActorLocation();
		projectileOriginOffset.Normalize();
		projectileOriginOffset *= detectionRange;
		// projectileOrigin += GetActorLocation();

		projectileDestination = racer->GetActorLocation();
		hasSetProjectileOrigin = true;
	}
}

void AClass_ProjectileStormEncounter::SpawnProjectile(){
	// AActor* target = victims[currentIndex];

	currentIndex++;
	currentIndex %= victims.Num();
	
	FRotator random = {UKismetMathLibrary::RandomFloatInRange(-90,90), UKismetMathLibrary::RandomFloatInRange(-90,90), UKismetMathLibrary::RandomFloatInRange(-90,90)};
	
	FRotator rotation{UKismetMathLibrary::RandomFloatInRange(0,360),UKismetMathLibrary::RandomFloatInRange(0,360),UKismetMathLibrary::RandomFloatInRange(0,360)};
			

    FTransform blankTransform;
	// float random = detectionRange / 2; 
    blankTransform.SetLocation(	GetActorLocation() + random.RotateVector(projectileOriginOffset) );	
	blankTransform.SetRotation(rotation.Quaternion());

	float scale = UKismetMathLibrary::RandomFloatInRange(minScale,maxScale);
	blankTransform.SetScale3D(FVector{scale, scale, scale});

    FActorSpawnParameters spawnParams;

	AActor* temp = GetWorld()->SpawnActor<AActor>(projectilePtr, blankTransform, spawnParams);

	if(temp){
		if(applyPhysics){
			UPrimitiveComponent* physicsBody = Cast<UPrimitiveComponent>(temp->GetRootComponent());
			if(!physicsBody){
        		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Uprimitivecomponent for spawned actor not found even though applyPhysics is true for Class ProjectileStormEncounter, method cancelled"));
				return;
			}

			FVector impulseVector = (projectileDestination - (projectileOriginOffset + GetActorLocation())).GetSafeNormal() * projectileSpeed;
			physicsBody->SetSimulatePhysics(true);
			physicsBody->AddImpulse(impulseVector, "", true);
		}
		if(projectileLifetime > 0){
			// UClass_LifetimeComponent* timer = NewObject<UClass_LifetimeComponent>();
			// temp->AddComponentByClass(UClass_LifetimeComponent, false, FTransform{}, true);
			timeQueue.Enqueue(projectileLifetime);
			projectileQueue.Enqueue(temp);
		}
	}
}

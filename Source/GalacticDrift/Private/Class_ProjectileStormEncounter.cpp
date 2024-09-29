// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_ProjectileStormEncounter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Class_LifetimeComponent.h"
#include "Class_FracturedActor.h"

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

	if(!projectile){
		projectile = GetComponentByClass<UStaticMeshComponent>();
	}
	if(!projectile){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no static mesh found for class projectile storm encounter"));
	}
	else{

		// FAttachmentTransformRules rules{EAttachmentRule::SnapToTarget, false};
		// staticMeshTemplate->AttachToComponent(GetRootComponent(), rules);

		// staticMeshTemplate->SetStaticMesh(projectile->GetStaticMesh());
		// staticMeshTemplate->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		// staticMeshTemplate->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

		// staticMeshTemplate->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		// staticMeshTemplate->SetNotifyRigidBodyCollision(true);

		// staticMeshTemplate->SetRelativeScale3D(FVector{5,5,5});
		// staticMeshTemplate->OnComponentHit.AddDynamic(this, &AClass_StaticSpawner::EventHit);

		projectile->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		projectile->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

		projectile->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		projectile->SetNotifyRigidBodyCollision(true);

		projectile->OnComponentHit.AddDynamic(this, &AClass_ProjectileStormEncounter::EventHit);
		projectile->SetRelativeScale3D(FVector{0,0,0});
		// projectile->SetScale3D(FVector{0,0,0});

		// staticMeshTemplate->OnComponentBeginOverlap.AddDynamic( this, &AClass_StaticSpawner::BeginOverlap );

	}
}

// Called every frame
void AClass_ProjectileStormEncounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(eventActive && duration > 0){
		duration -= DeltaTime;
		// UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), duration);
        // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("event active"));
		if(duration <= 0){
			// EndEvent();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("END EVENT NOW"));
		}
		else{
			// spawnTimer = spawnInterval;
			SpawnProjectile();
		}
	}

	if(timeQueue.IsEmpty() && projectileQueue.IsEmpty()){
		timePassed = 0;
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("timePassed = 0"));
		if(eventActive && duration <= 0){
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("calling end event"));
			EndEvent();
		}
	}
	else if(!timeQueue.IsEmpty() && !projectileQueue.IsEmpty()){

		float* mostRecent = timeQueue.Peek();
		if(!mostRecent){
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HOW IS IT POSSIBLE FLOAT NULLPTR"));
		}
		else{
			(*mostRecent) -= DeltaTime;
		}

		timePassed += DeltaTime;

		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FText::FromString(FString::SanitizeFloat(timePassed)));
		if(*mostRecent <= 0){
		// if(timePassed >= *mostRecent){
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ready to destroy asteroid"));

			if(projectileQueue.Peek()){
				UStaticMeshComponent* temp = *projectileQueue.Peek();
				if(temp && projectiles.Contains(temp)){
					projectiles.Remove(temp);
					temp->DestroyComponent(true);
					// actor->K2_DestroyActor();
					// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("destroying asteroid in projectile storm"));
				}
			}
			projectileQueue.Pop();
			timeQueue.Pop();

			// timePassed -= spawnInterval;
			if(!timeQueue.IsEmpty()){
				float* nextRecent = timeQueue.Peek();
				if(nextRecent){
					(*nextRecent) -= timePassed;
				}
				else{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HOW IS IT POSSIBLE FLOAT NULLPTR"));
				}
			}
		}
	}
	else{
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: timeQueue and projectileQueue not same size in Class ProjectileStormEncounter?"));
	}

	// if(timeQueue.IsEmpty() && projectileQueue.IsEmpty()){
	// 	timePassed = 0;
	// 	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("timePassed = 0"));
	// 	if(eventActive && duration <= 0){
	// 		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("calling end event"));
	// 		EndEvent();
	// 	}
	// }
	// else if(!timeQueue.IsEmpty() && !projectileQueue.IsEmpty()){

	// 	float* mostRecent = timeQueue.Peek();
	// 	if(!mostRecent){
	// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HOW IS IT POSSIBLE FLOAT NULLPTR"));
	// 	}
	// 	else{
	// 		(*mostRecent) -= DeltaTime;
	// 	}

	// 	timePassed += DeltaTime;

	// 	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FText::FromString(FString::SanitizeFloat(timePassed)));
	// 	if(*mostRecent <= 0){
	// 	// if(timePassed >= *mostRecent){
	// 		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ready to destroy asteroid"));

	// 		if(projectileQueue.Peek()){
	// 			AActor* actor = *projectileQueue.Peek();
	// 			if(actor && !actor->IsActorBeingDestroyed() && !actor->IsPendingKillPending()){
	// 				actor->K2_DestroyActor();
	// 				// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("destroying asteroid in projectile storm"));
	// 			}
	// 			else{
	// 				// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Couldnt get actor ptr off queue peek in Class ProjectileStormEncounter?"));
	// 			}
	// 		}
	// 		projectileQueue.Pop();
	// 		timeQueue.Pop();

	// 		// timePassed -= spawnInterval;
	// 		if(!timeQueue.IsEmpty()){
	// 			float* nextRecent = timeQueue.Peek();
	// 			if(nextRecent){
	// 				(*nextRecent) -= timePassed;
	// 			}
	// 			else{
	// 				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HOW IS IT POSSIBLE FLOAT NULLPTR"));
	// 			}
	// 		}
	// 	}
	// }
	// else{
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: timeQueue and projectileQueue not same size in Class ProjectileStormEncounter?"));
	// }
}

bool AClass_ProjectileStormEncounter::BeginEvent(){
	bool result = AClass_Encounter::BeginEvent();
	if(result && eventCollider){
		eventCollider->SetGenerateOverlapEvents(false);
	}else if(result){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no eventCollider in encounter???"));
	}
	return result;
}

void AClass_ProjectileStormEncounter::EndEvent(){
	AClass_Encounter::EndEvent();
	// while(!projectileQueue.IsEmpty()){
	// 	if(projectileQueue.Peek()){
	// 		AActor* actor = *projectileQueue.Peek();
	// 		if(actor){
	// 			actor->K2_DestroyActor();
	// 		}
	// 		else{
	// 			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Couldnt get actor ptr off queue peek in Class ProjectileStormEncounter?"));
	// 		}
	// 	}
	// 	projectileQueue.Pop();
	// 	if(!timeQueue.IsEmpty()){
	// 		timeQueue.Pop();
	// 	}
	// }
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("end asteroid storm event in projectilestormencounter"));
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

	// currentIndex++;
	// currentIndex %= victims.Num();
	
	// FRotator random = {UKismetMathLibrary::RandomFloatInRange(-90,90), UKismetMathLibrary::RandomFloatInRange(-90,90), UKismetMathLibrary::RandomFloatInRange(-90,90)};
	FRotator random = {UKismetMathLibrary::RandomFloatInRange(-70,70), UKismetMathLibrary::RandomFloatInRange(-70,70), UKismetMathLibrary::RandomFloatInRange(-70,70)};
	
	FRotator rotation{UKismetMathLibrary::RandomFloatInRange(0,360),UKismetMathLibrary::RandomFloatInRange(0,360),UKismetMathLibrary::RandomFloatInRange(0,360)};
			

    FTransform blankTransform;
	// float random = detectionRange / 2; 
    blankTransform.SetLocation(	GetActorLocation() + random.RotateVector(projectileOriginOffset) );	
    // blankTransform.SetLocation(	GetActorLocation() + projectileOriginOffset );	
	blankTransform.SetRotation(rotation.Quaternion());

	float scale = UKismetMathLibrary::RandomFloatInRange(minScale,maxScale);
	blankTransform.SetScale3D(FVector{scale, scale, scale});

    FActorSpawnParameters spawnParams;


	UStaticMeshComponent* temp = DuplicateObject <UStaticMeshComponent> (projectile, this);
	if(temp){
		temp->SetStaticMesh(projectile->GetStaticMesh());
		FinishAddComponent(Cast<UActorComponent>(temp), false, blankTransform);
		// temp->OnComponentHit.AddDynamic(this, &AClass_StaticSpawner::EventHit);
		FVector impulseVector = (projectileDestination - (projectileOriginOffset + GetActorLocation())).GetSafeNormal() * projectileSpeed;
		temp->SetSimulatePhysics(true);
		temp->AddImpulse(impulseVector, "", true);

		if(projectileRotationSpeed > 0){
			FVector randomAngular{UKismetMathLibrary::RandomFloatInRange(-1,1), UKismetMathLibrary::RandomFloatInRange(-1,1), UKismetMathLibrary::RandomFloatInRange(-1,1)};
			temp->AddAngularImpulseInDegrees(randomAngular.GetSafeNormal() * projectileRotationSpeed, "", true);
		}
		
		// temp->SetHiddenInGame(true,true);
		projectiles.Add(temp, projectileHealth);

		timeQueue.Enqueue(projectileLifetime);
		projectileQueue.Enqueue(temp);

		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("successfully spawned"));
	}

	// AActor* temp = GetWorld()->SpawnActor<AActor>(projectilePtr, blankTransform, spawnParams);

	// if(temp){
	// 	temp->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 	temp->GetRootComponent()->SetWorldScale3D(FVector{scale, scale, scale});

	// 	if(applyPhysics){
	// 		UPrimitiveComponent* physicsBody = Cast<UPrimitiveComponent>(temp->GetRootComponent());
	// 		if(!physicsBody){
    //     		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: Uprimitivecomponent for spawned actor not found even though applyPhysics is true for Class ProjectileStormEncounter, method cancelled"));
	// 			return;
	// 		}

	// 		FVector impulseVector = (projectileDestination - (projectileOriginOffset + GetActorLocation())).GetSafeNormal() * projectileSpeed;
	// 		physicsBody->SetSimulatePhysics(true);
	// 		physicsBody->AddImpulse(impulseVector, "", true);
	// 	}
	// 	if(projectileLifetime > 0){
	// 		// UClass_LifetimeComponent* timer = NewObject<UClass_LifetimeComponent>();
	// 		// temp->AddComponentByClass(UClass_LifetimeComponent, false, FTransform{}, true);
	// 		// timeQueue.Enqueue(projectileLifetime);
	// 		// projectileQueue.Enqueue(temp);
	// 	}
	// }
}

void AClass_ProjectileStormEncounter::EventHit
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

		UStaticMeshComponent* otherMeshComponent = Cast<UStaticMeshComponent>(OtherComp);

		// if two projectiles of projectile storm collide with each other
		if(otherMeshComponent && projectiles.Contains(otherMeshComponent)){
			return;
		}

		if(myComp && projectiles.Contains(myComp)){
			projectiles[myComp] -= 10;
			if(projectiles[myComp] <= 0){

				FActorSpawnParameters spawnParams;			

				AActor* temp = GetWorld()->SpawnActor<AActor>(destroyedProjectilePtr, myComp->GetComponentTransform(), spawnParams);

				if(temp){
					temp->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

					temp->GetRootComponent()->SetWorldScale3D(myComp->GetComponentTransform().GetScale3D());
				}
				UPrimitiveComponent* tempRoot = Cast<UPrimitiveComponent>(temp->GetRootComponent());
				if(tempRoot && OtherComp){
					// tempRoot->AddImpulse(myComp->GetComponentVelocity(),"",true);
					tempRoot->AddImpulse(OtherComp->GetComponentLocation() - myComp->GetComponentLocation(),"",true);
				}
				projectiles.Remove(myComp);
				myComp->DestroyComponent(true);

			}
		}
	}
					  
}
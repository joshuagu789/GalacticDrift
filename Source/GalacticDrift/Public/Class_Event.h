/*
NOTE: collider overlap detection only detects physics bodies- AKA ONLY DETECTS RACERS!
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "Class_RacingGameInstance.h"
#include "Class_RacingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Header_Enumerations.h"
#include "Components/SphereComponent.h"
#include "Class_Racer_Pawn.h"
#include "Class_Waypoint_Actor.h"
#include "Class_Event.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Event : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_Event();

	UFUNCTION()
		/*
		Returns false if event already playing
		*/
		virtual bool BeginEvent();
	UFUNCTION()
		virtual void EndEvent();
	UFUNCTION()
		virtual bool RevealToRacers(AClass_Racer_Pawn* racer);	// typically through marker component
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> waypoint;
	UPROPERTY()
		AClass_Waypoint_Actor* currentWaypointActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText waypointTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* eventCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float detectionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool startEventOnBeginPlay = false;

	bool eventActive = false;
	bool isRevealed = false;
	UPROPERTY()
		AClass_RacingGameMode* server;

private:


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult );

	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("u shall work!"));
// }

};

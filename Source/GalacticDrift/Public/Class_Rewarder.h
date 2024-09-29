/*
Any event that has ability to reward racers
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Event.h"
#include "Class_Rewarder.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Rewarder : public AClass_Event
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_Rewarder();

	// bool BeginEvent();
	// void EndEvent();
	// bool RevealToRacers();

	UFUNCTION()
		virtual void RewardRacer(AClass_Racer_Pawn* racer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* rewardCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rewardRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int numberOfRewards;

	UPROPERTY()
		TSet<AClass_Racer_Pawn*> rewarded;
	bool readyToReward = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    void RewardBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult );
};

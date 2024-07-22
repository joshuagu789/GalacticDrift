/*
Goal for racers to reach that rewards racers on reaching destination, typically has some sort of challenge?
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class_Event.h"
#include "Class_Objective.generated.h"

UCLASS()
class GALACTICDRIFT_API AClass_Objective : public AClass_Event
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClass_Objective();

	UFUNCTION()
		virtual void RewardPlayer(AActor* player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		int numberOfRewards;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

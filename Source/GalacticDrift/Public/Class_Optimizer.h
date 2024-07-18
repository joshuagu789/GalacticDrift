/*
Entities with this component (typically racers both npc and player) unfreezes any object it approaches and freezes the object upon leaving
*/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Class_Freezable.h"
#include "Class_Optimizer.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_Optimizer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Optimizer();

	UFUNCTION(BlueprintCallable)
		/*
		Tries to enable actor by unfreezing actor's freezable components
		*/
		void AttemptToEnableActor(AActor* actor);
	UFUNCTION(BlueprintCallable)
		/*
		Tries to disable actor by freezing actor's freezable components
		*/
		void AttemptToDisableActor(AActor* actor);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 	UPrimitiveComponent* collider;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 	AActor* actorCollider;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// //OnOverlapBegin
	// void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	// 								bool bFromSweep, const FHitResult& SweepResult);
	// void OnActorBeginOverlap(AActor* OtherActor);
	// void OnComponentEndOverlap	(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);	
};

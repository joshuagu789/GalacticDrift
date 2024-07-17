/*
Entities with this component (typically racers both npc and player) unfreezes any object it approaches and freezes the object upon leaving
*/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"

#include "Class_Optimizer.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS( ClassGroup=(Custom), Blueprintable )
class GALACTICDRIFT_API UClass_Optimizer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClass_Optimizer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPrimitiveComponent* collider;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									bool bFromSweep, const FHitResult& SweepResult);
		
};

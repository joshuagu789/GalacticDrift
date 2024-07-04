// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Sensor.h"

// Sets default values for this component's properties
UClass_Sensor::UClass_Sensor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_Sensor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClass_Sensor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TMap<TEnumAsByte<MarkerType>, FVector> UClass_Sensor::ScanMarkers(const TSet<AActor*> &markers){
	
	TMap<TEnumAsByte<MarkerType>, FVector> temp;
	return temp;
}

TArray<FString> UClass_Sensor::ScanMarkersStrings(const TSet<AActor*> &markers){
	TArray<FString> temp;
	for(auto marker: markers){
		if(marker){
			FString markerName = marker->GetComponentByClass<UClass_Marker>()->GetMarkerName();
			FVector location = marker->GetActorLocation();
			float inaccuracyValue = 500000-500000*accuracy;	// max inaccuracy offset to add/subtract from a coordinate
			FVector inaccuracy(UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue), UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue), UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue));
			location += inaccuracy;
			
			FString output = markerName + FString(": (") + FString::FromInt(static_cast<int>(location.X)) + FString(",") + FString::FromInt(static_cast<int>(location.Y)) + FString(",") + FString::FromInt(static_cast<int>(location.Z)) + FString(")");
			// FText::Format(FText::FromString(markerName), UKismetTextLibrary::Conv_VectorToText(location))
			// temp.Add(markerName, location);
			temp.Add(output);	// sort array by distance?
		} else {
        	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: dangling pointer in Class_Sensors's ScanMarkersStrings from game instance markerList"));
		}
	}
	return temp;
}

// TMap<FString, FVector> UClass_Sensor::ScanMarkersStrings(const TSet<AActor*> &markers){
// 	TMap<FString, FVector> temp;
// 	for(auto marker: markers){
// 		FString markerName = marker->GetComponentByClass<UClass_Marker>()->GetMarkerName();
// 		FVector location = marker->GetActorLocation();
// 		float inaccuracyValue = 500000-500000*accuracy;	// max inaccuracy offset to add/subtract from a coordinate
// 		FVector inaccuracy(UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue), UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue), UKismetMathLibrary::RandomFloatInRange(-inaccuracyValue,inaccuracyValue));
// 		location += inaccuracy;
// 		temp.Add(markerName, location);
// 	}
// 	return temp;
// }

void UClass_Sensor::TakeDamage(float damage){ health -= damage; }
void UClass_Sensor::Repair(float amount){ health += amount; }
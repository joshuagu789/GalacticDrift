/*
	Contains many methods for returning information, many of which could be used for ui
*/
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Class_ActorInformationTracker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UClass_ActorInformationTracker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GALACTICDRIFT_API IClass_ActorInformationTracker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

    UFUNCTION(BlueprintCallable, Category="Information")
        virtual FString GetSpeedIntAsString();
    UFUNCTION(BlueprintCallable, Category="Information")
        virtual float GetSpeedFloat(int decimalPlaces);
    UFUNCTION(BlueprintCallable, Category="Information")
        virtual int GetSpeedInt();
    // UFUNCTION(BlueprintCallable, Category="Information")
    //     virtual void UnRagdoll();
    // UFUNCTION(BlueprintCallable, Category="Information")
    //     virtual void UnRagdoll();

};

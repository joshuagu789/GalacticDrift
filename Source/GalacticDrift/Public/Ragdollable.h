// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ragdollable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class URagdollable : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class GALACTICDRIFT_API IRagdollable
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    
    UFUNCTION(BlueprintCallable, Category="Action")
        virtual void RagdollFor(float duration);
    
    UFUNCTION(BlueprintCallable, Category="Action")
        virtual void UnRagdoll();
};

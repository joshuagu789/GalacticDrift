// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Class_PlayerUI.h"

// Sets default values for this component's properties
UClass_PlayerUI::UClass_PlayerUI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClass_PlayerUI::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AClass_Racer_Pawn* owner = Cast<AClass_Racer_Pawn>(GetOwner());
	if(owner){
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetOwner(), 0);
		if(playerController){
			HUD = Cast<AClass_InGameHUD>(playerController->GetHUD());
			if(HUD){
				widget = HUD->GetWidget();
				if(!widget){
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("UClass_InGameWidget not found for player ui"));
				}
			}
			else{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AClass InGameHUD not found for player ui"));
			}
		}
		else{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("APlayerController not found for player ui"));
		}
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("why attach player ui to something not class racer pawn lol"));
	}
}


// Called every frame
void UClass_PlayerUI::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(!widget){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("no widget"));
	}
}

void UClass_PlayerUI::RelayMessageToConsole(FString message){
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("relaying message to console in playerui"));
	if(widget){
		widget->PushLineToOutputConsole(message);
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: widget is nullptr in UClass_PlayerUI::RelayMessageToConsole"));
	}
}

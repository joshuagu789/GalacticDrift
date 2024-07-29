// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Waypoint_Actor.h"

// Sets default values
AClass_Waypoint_Actor::AClass_Waypoint_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClass_Waypoint_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClass_Waypoint_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorTickInterval(0.5);
	if(timer <= 0 && ready){
		if(!widgetPtr){
			UWidgetComponent* temp = FindComponentByClass<UWidgetComponent>();
			if(temp){
				
				UUserWidget* temp2 = Cast<UUserWidget>( temp->GetWidget() );
				if(temp2){

					widgetPtr = Cast<UClass_Waypoint_Widget>( temp2 );
					if(widgetPtr){
						textPtr = widgetPtr->GetTextPtr();
						if(!textPtr){
				    		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: textPtr is null for class waypoint actor"));
						}
					}
					else{
			    		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: widgetPtr isnt UClass_Waypoint_Widget for class waypoint actor"));
					}
				}
				else{
		    		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no widgetclass for uwidget component for class waypoint actor"));
				}
			}
			else{
	    		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: no uwidgetcomponent for class waypoint actor"));
			}
		}
		if(textPtr && racer){
			UpdateWaypointText();
		}
		timer += 0.5;

	}else{
		timer -= DeltaTime;
	}
}

void AClass_Waypoint_Actor::ConfigureWaypoint(const FText& categoryText, const FText& titleText, AClass_Racer_Pawn* racerTarget){
	category = categoryText;
	title = titleText;

	outputText = FText::Join(NSLOCTEXT("a","b",""), FText::FromString("["), category);	// need FString("[")?
	outputText = FText::Join(NSLOCTEXT("a","b",""), outputText, FText::FromString("]\n"));
	outputText = FText::Join(NSLOCTEXT("a","b",""), outputText, title);
	outputText = FText::Join(NSLOCTEXT("a","b",""), outputText, FText::FromString("\nDIST "));

	if(!racerTarget){
	    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: racerTarget is nullptr in ConfigureWaypoint in AClass Waypoint Actor"));
		return;
	}
	racer = racerTarget;
	ready = true;
}

void AClass_Waypoint_Actor::UpdateWaypointText(){
	if(textPtr && racer){
		float speedSquared = racer->GetVelocity().SizeSquared();
		if(speedSquared <= 0){
			speedSquared = 1;
		}
		// int time = (int) (GetActorLocation() - racer->GetActorLocation()).SizeSquared()  / (speedSquared);	// DO NOT DIVIDE BY ZERO
		                    // FText character = FText::FromString( line.Mid(lineIndex, 1) );
		int distance  = (GetActorLocation() - racer->GetActorLocation()).Size() / 1000;
		// FText temp =  FText::Join(NSLOCTEXT("a","b",""), outputText,  FText::FromString( FString::FromInt(time) ));
		textPtr->SetText( FText::Join(NSLOCTEXT("a","b",""), outputText,  FText::FromString(FString::FromInt(distance))) );
	}
	else{
	    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: UpdateWaypointText called when textPtr and/or racer null in AClass Waypoint Actor"));
	}
}

void AClass_Waypoint_Actor::SetCategory(FText categoryText){
	category = categoryText;
	outputText = FText::Join(NSLOCTEXT("a","b",""), FText::FromString("["), category);	// need FString("[")?
	outputText = FText::Join(NSLOCTEXT("a","b",""), outputText, FText::FromString("]\n"));
	outputText = FText::Join(NSLOCTEXT("a","b",""), outputText, title);
	outputText = FText::Join(NSLOCTEXT("a","b",""), outputText, FText::FromString("\nDIST "));
}

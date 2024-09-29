// Fill out your copyright notice in the Description page of Project Settings.


#include "Class_Waypoint_Widget.h"

UTextBlock* UClass_Waypoint_Widget::GetTextPtr(){
    if(!textPtr){
	    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: textPtr is nullptr on GetTexPtr in Class_Waypoint_Widget"));
    }
    return textPtr;
}

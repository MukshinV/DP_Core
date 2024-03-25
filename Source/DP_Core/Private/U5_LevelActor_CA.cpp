// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_LevelActor_CA.h"

#include "EventSystem/U5_Event_BlueprintLibrary.h"


AU5_LevelActor_CA::AU5_LevelActor_CA()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AU5_LevelActor_CA::StartGame_Implementation()
{
	Super::StartGame_Implementation();

	FString eventString{};
	UU5_Event_BlueprintLibrary::EventHandleToString(eventString, LoadStateEventHandle); 
	UU5_Event_BlueprintLibrary::SetEventValue(GetWorld(), eventString, 1.0f);

	RunDefaultEventValues_Implementation();
}

void AU5_LevelActor_CA::RunDefaultEventValues_Implementation()
{
}


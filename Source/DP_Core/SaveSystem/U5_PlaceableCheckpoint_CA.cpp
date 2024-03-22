// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_PlaceableCheckpoint_CA.h"

#include "Kismet/GameplayStatics.h"
#include "UnrealCore/U5_GameInstace.h"
#include "Utils/U5_Utils.h"


AU5_PlaceableCheckpoint_CA::AU5_PlaceableCheckpoint_CA()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AU5_PlaceableCheckpoint_CA::LoadCheckpoint()
{
	const UWorld* world = GetWorld();
	const UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(UGameplayStatics::GetGameInstance(world));
	
	gameInstance->GetCheckpointSystem()->LoadCheckpoint(this);
	mU5_DEBUGOUT(true, L"Loaded checkpoint: " << mDNAME(this));
}



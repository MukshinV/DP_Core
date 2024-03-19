// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_DebugCheckpoint_CA.h"

#include "Kismet/GameplayStatics.h"
#include "UnrealCore/U5_GameInstace.h"
#include "Utils/U5_Utils.h"


AU5_DebugCheckpoint_CA::AU5_DebugCheckpoint_CA()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AU5_DebugCheckpoint_CA::LoadCheckpoint()
{
	const UWorld* world = GetWorld();
	const UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(UGameplayStatics::GetGameInstance(world));
	
	gameInstance->GetCheckpointSystem()->LoadDebugCheckpoint(this);
	mU5_DEBUGOUT(true, L"Loaded debug checkpoint: " << mDNAME(this));
}



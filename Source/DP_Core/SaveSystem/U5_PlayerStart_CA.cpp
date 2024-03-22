// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_PlayerStart_CA.h"

#include "Kismet/GameplayStatics.h"
#include "UnrealCore/U5_GameInstace.h"


AU5_PlayerStart_CA::AU5_PlayerStart_CA()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AU5_PlayerStart_CA::BeginPlay()
{
	Super::BeginPlay();

	RegisterInCheckpointSystem_Internal();
}

void AU5_PlayerStart_CA::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterFromCheckpointSystem_Internal();
	
	Super::EndPlay(EndPlayReason);
}

void AU5_PlayerStart_CA::RegisterInCheckpointSystem_Internal()
{
	UWorld* world = GetWorld();
	const UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(UGameplayStatics::GetGameInstance(world));

	if(gameInstance)
	{
		gameInstance->GetCheckpointSystem()->RegisterPlayerStart(this);
	}
}

void AU5_PlayerStart_CA::UnregisterFromCheckpointSystem_Internal()
{
	UWorld* world = GetWorld();
	const UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(UGameplayStatics::GetGameInstance(world));

	if(gameInstance)
	{
		gameInstance->GetCheckpointSystem()->UnregisterPlayerStart(this);
	}
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_CheckpointSystem_CU.h"

#include "UnrealCore/U5_GameInstace.h"
#include "DP_Core/Utils/U5_Utils.h"
#include "Kismet/GameplayStatics.h"

void FU5_CheckpointState_Struct::ResetCheckpointState()
{
	PlayerTransform = FTransform{};
	LevelName.Reset();
}

UU5_CheckpointSystem_CU::UU5_CheckpointSystem_CU()
{
}

void UU5_CheckpointSystem_CU::Initialize(UU5_GameInstance* _gameInstance)
{
	GameInstance = _gameInstance;	
}

void UU5_CheckpointSystem_CU::SaveGameState()
{
	const UWorld* currentWorld = GameInstance->GetWorld();
	const FString currentLevelName = UGameplayStatics::GetCurrentLevelName(currentWorld);

	FU5_CheckpointState_Struct newCheckpoint{};
	newCheckpoint.LevelName = currentLevelName;
	
	if(!TrySavePlayerState(newCheckpoint)) return;
	
	LastCheckpointData = MoveTemp(newCheckpoint);
	mU5_DEBUGOUT(true, L"Checkpoint saved");
}

void UU5_CheckpointSystem_CU::LoadDebugCheckpoint(AU5_DebugCheckpoint_CA* _checkpointActor)
{
	LastCheckpointData.PlayerTransform = _checkpointActor->GetActorTransform();
	LoadLastMapCheckpointState();
}

void UU5_CheckpointSystem_CU::LoadLastMapCheckpointState()
{
	if(!GameInstance->LocalController) return;

	APawn* controlledPawn = GameInstance->LocalController->GetPawn();

	if(controlledPawn)
	{
		controlledPawn->SetActorTransform(LastCheckpointData.PlayerTransform);
	}
}

bool UU5_CheckpointSystem_CU::TrySavePlayerState(FU5_CheckpointState_Struct& _targetCheckpointState) const
{
	if(!GameInstance->LocalController) return false;

	const APawn* controlledPawn = GameInstance->LocalController->GetPawn();

	if(!controlledPawn) return false;

	_targetCheckpointState.PlayerTransform = controlledPawn->GetActorTransform();

	return true;
}

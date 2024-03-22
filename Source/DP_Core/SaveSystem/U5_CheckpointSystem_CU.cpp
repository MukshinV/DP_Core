// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_CheckpointSystem_CU.h"

#include "EngineUtils.h"
#include "UnrealCore/U5_GameInstace.h"
#include "DP_Core/Utils/U5_Utils.h"
#include "Engine/PlayerStartPIE.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
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

void UU5_CheckpointSystem_CU::OnBeforeLevelActorPlay()
{
#if WITH_EDITOR
	
	const UWorld* world = GameInstance->GetWorld();
	const AActor* piePlayerStart = UGameplayStatics::GetActorOfClass(world, APlayerStartPIE::StaticClass());

	if(piePlayerStart)
	{
		TArray<AActor*> foundPlayerControllers{};
		TArray<AActor*> foundGamePlayerStarts{};

		const AActor* playerStart = UGameplayStatics::GetActorOfClass(world, APlayerStart::StaticClass());
		UGameplayStatics::GetAllActorsOfClass(world, APlayerController::StaticClass(), foundPlayerControllers);
		UGameplayStatics::GetAllActorsOfClass(world, AU5_PlayerStart_CA::StaticClass(), foundGamePlayerStarts);

		for(int32 i = 0; i < foundPlayerControllers.Num(); ++i)
		{
			const APlayerController* playerController = Cast<APlayerController>(foundPlayerControllers[i]);
			const bool shouldSpawnAtSpot = playerController != nullptr && playerController->StartSpot != nullptr;

			if(!shouldSpawnAtSpot) continue;

			APawn* controlledPawn = playerController->GetPawn();

			if(!controlledPawn) continue;

			if(playerStart)
			{
				controlledPawn->SetActorLocation(playerStart->GetActorLocation());
			}
			else
			{
				controlledPawn->SetActorLocation(FVector{0.0f, 0.0f, 0.0f});
			}
		}

		for (int32 i = 0; i < foundGamePlayerStarts.Num(); ++i)
		{
			foundGamePlayerStarts[i]->SetActorLocation(piePlayerStart->GetActorLocation());
		}
	}

#endif
}

void UU5_CheckpointSystem_CU::OnBeforeLevelActorEndPlay()
{
}

AU5_PlayerStart_CA* UU5_CheckpointSystem_CU::GetPlayerStart() const
{
	return LevelPlayerStart;
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

void UU5_CheckpointSystem_CU::LoadCheckpoint(AU5_PlaceableCheckpoint_CA* _checkpointActor)
{
	LastCheckpointData.PlayerTransform = _checkpointActor->GetActorTransform();
	LoadLastMapCheckpointState();
}

void UU5_CheckpointSystem_CU::RegisterPlayerStart(AU5_PlayerStart_CA* _playerStart)
{
	LevelPlayerStart = _playerStart;
}

void UU5_CheckpointSystem_CU::UnregisterPlayerStart(AU5_PlayerStart_CA* _playerStart)
{
	check(LevelPlayerStart);
	LevelPlayerStart = nullptr;
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

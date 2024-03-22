// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "U5_PlaceableCheckpoint_CA.h"
#include "U5_PlayerStart_CA.h"
#include "U5_CheckpointSystem_CU.generated.h"

USTRUCT()
struct FU5_CheckpointState_Struct
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FTransform PlayerTransform;
	UPROPERTY()
	FString LevelName;

	FU5_CheckpointState_Struct() = default;
	void ResetCheckpointState();
};

class UU5_GameInstance;

UCLASS(Blueprintable)
class DP_CORE_API UU5_CheckpointSystem_CU : public UObject
{
	GENERATED_BODY()

public:
	UU5_CheckpointSystem_CU();
	
	void Initialize(UU5_GameInstance* _gameInstance);
	void OnBeforeLevelActorPlay();
	void OnBeforeLevelActorEndPlay();

	UFUNCTION(BlueprintCallable, DisplayName="!GetPlayerStart(C)")
	AU5_PlayerStart_CA* GetPlayerStart() const;
	UFUNCTION(BlueprintCallable, DisplayName="!SaveGameState(C)")
	void SaveGameState();
	UFUNCTION(BlueprintCallable, DisplayName="!LoadLastMapCheckpointState(C)")
	void LoadLastMapCheckpointState();
	UFUNCTION(BlueprintCallable, DisplayName="!LoadDebugCheckpoint(C)(DebugCheckpoint_CA)")
	void LoadCheckpoint(AU5_PlaceableCheckpoint_CA* _checkpointActor);
	UFUNCTION(BlueprintCallable, DisplayName="!RegisterPlayerStart(C)(AU5_PlayerStart_CA)")
	void RegisterPlayerStart(AU5_PlayerStart_CA* _playerStart);
	UFUNCTION(BlueprintCallable, DisplayName="!UnregisterPlayerStart(C)(AU5_PlayerStart_CA)")
	void UnregisterPlayerStart(AU5_PlayerStart_CA* _playerStart);

private:
	bool TrySavePlayerState(FU5_CheckpointState_Struct& _targetCheckpointState) const;
	
	TObjectPtr<UU5_GameInstance> GameInstance;
	TObjectPtr<AU5_PlayerStart_CA> LevelPlayerStart;
	
	FU5_CheckpointState_Struct LastCheckpointData;
};


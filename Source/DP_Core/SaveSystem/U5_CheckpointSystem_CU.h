// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "U5_CheckpointSystem_CU.generated.h"

USTRUCT()
struct FU5_CheckpointState_Struct
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FTransform PlayerTransform;
	UPROPERTY()
	FRotator PlayerRotation;
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
	
	UFUNCTION(BlueprintCallable, DisplayName="!SaveGameState(C)")
	void SaveGameState();
	UFUNCTION(BlueprintCallable, DisplayName="!LoadLastMapCheckpointState(C)")
	void LoadLastMapCheckpointState();

private:
	bool TrySavePlayerState(FU5_CheckpointState_Struct& _targetCheckpointState) const;
	
	UPROPERTY()
	TObjectPtr<UU5_GameInstance> GameInstance;
	UPROPERTY()
	FU5_CheckpointState_Struct LastCheckpoint;
};

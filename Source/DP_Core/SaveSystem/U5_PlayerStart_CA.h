// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "U5_PlayerStart_CA.generated.h"

UCLASS()
class DP_CORE_API AU5_PlayerStart_CA : public AActor
{
	GENERATED_BODY()

public:
	AU5_PlayerStart_CA();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	void RegisterInCheckpointSystem_Internal();
	void UnregisterFromCheckpointSystem_Internal();
};

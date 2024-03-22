// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "U5_PlaceableCheckpoint_CA.generated.h"

UCLASS()
class DP_CORE_API AU5_PlaceableCheckpoint_CA : public AActor
{
	GENERATED_BODY()

public:
	AU5_PlaceableCheckpoint_CA();

	UFUNCTION(BlueprintCallable, DisplayName="!LoadCheckpoint(C)(Virtual)")
	virtual void LoadCheckpoint();
};

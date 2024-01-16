// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "U5_Level_CA.generated.h"

UCLASS()
class DP_CORE_API AU5_Level_CA : public AActor
{
	GENERATED_BODY()
	
public:	
	AU5_Level_CA()
	{
		PrimaryActorTick.bCanEverTick = false;
	}


protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type _reason) override;

public:
	virtual void Tick(float DeltaTime) override;

};

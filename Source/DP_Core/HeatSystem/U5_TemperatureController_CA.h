﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "U5_TemperatureController_CA.generated.h"

USTRUCT(BlueprintType)
struct FU5_TemperatureSourceParameters_Struct : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@TargetTemperature")
	float TargetTemperature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@TemperatureSpeed")
	float TemperatureSpeed;
};

USTRUCT(BlueprintType)
struct FU5_TemperatureSource_Struct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@SourceName")
	FString SourceName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@SourceTemperature")
	float SourceTemperature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@SourceParameters")
	FU5_TemperatureSourceParameters_Struct SourceParameters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@IsRunning")
	bool bIsRunning;
};

UCLASS(Blueprintable)
class DP_CORE_API AU5_TemperatureController_CA : public AActor
{
	GENERATED_BODY()

public:
	AU5_TemperatureController_CA();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@TemperatureTable")
	TObjectPtr<UDataTable> TemperatureTable;
	UPROPERTY(BlueprintReadWrite, DisplayName="@CurrentTemperatureSources")
	TArray<FU5_TemperatureSource_Struct> CurrentSources;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/U5_Event_ACC.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@SourceTemperature")
	float SourceTemperature;
};

UCLASS(Blueprintable)
class DP_CORE_API AU5_TemperatureController_CA : public AActor
{
	GENERATED_BODY()

public:
	AU5_TemperatureController_CA();
protected:
	UPROPERTY(BlueprintReadWrite, DisplayName="@CurrentTemperatureSources")
	TMap<FString, FU5_TemperatureSource_Struct> CurrentSources;

	UFUNCTION(BlueprintCallable, DisplayName="!UpdateSource(C)(String, float)")
	void UpdateSource(const FString& _sourceName, float _sourceValue);
	UFUNCTION(BlueprintCallable, DisplayName="!CalculateTotalTemperature(C)")
	float CalculateTotalTemperature() const;
};


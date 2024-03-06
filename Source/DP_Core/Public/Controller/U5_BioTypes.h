// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_BioTypes.generated.h"

UENUM(BlueprintType)
enum class ECharacterTemperatureStatus : uint8
{
	Default = 0,
	Heating_1Tier,
	Heating_2Tier,
	Heating_3Tier,
	Freezing_1Tier,
	Freezing_2Tier,
	Freezing_3Tier
};

USTRUCT(BlueprintType)
struct FU5_TemperatureStatusData_Struct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="@StatusType")
	ECharacterTemperatureStatus StatusType = ECharacterTemperatureStatus::Default;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="@MaxStatusLimit")
	float MaxStatusLimit = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="@StaminaDamagePerSecond")
	float StaminaDamagePerSecond = 0.0f;
};

USTRUCT(BlueprintType)
struct FU5_BioTemperatureData_Struct : public FTableRowBase 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="@TemperatureStatusArray")
	TArray<FU5_TemperatureStatusData_Struct> TemperatureStatuses;
};

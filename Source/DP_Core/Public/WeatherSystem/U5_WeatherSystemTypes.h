﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "U5_WeatherSystemTypes.generated.h"

USTRUCT(BlueprintType)
struct FU5_WeatherLightData_Struct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, DisplayName="@Intensity")
	float Intensity{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@LightWorldRotation")
	FRotator LightWorldRotation{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@LightColor")
	FLinearColor LightColor{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@CastShadows")
	bool bCastShadows{};
	
	FU5_WeatherLightData_Struct() = default;

	void ResetLightData()
	{
		Intensity = 0.0f;
		LightWorldRotation = FRotator::ZeroRotator;
		LightColor = FLinearColor::White;
		bCastShadows = false;
	}
};

USTRUCT(BlueprintType)
struct FU5_WeatherShadowColorData_Struct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, DisplayName="@Intensity")
	float Intensity{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@SourceCubemapAngle")
	float SourceCubemapAngle{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@VolumetricScatteringIntensity")
	float VolumetricScatteringIntensity{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@CastShadows")
	bool bCastShadows{};
	
	FU5_WeatherShadowColorData_Struct() = default;
	void ResetShadowColorData()
	{
		Intensity = 0.0f;
		SourceCubemapAngle = 0.0f;
		VolumetricScatteringIntensity = 0.0f;
		bCastShadows = false;
	}
};

USTRUCT(BlueprintType)
struct FU5_WeatherHeightFog_Struct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, DisplayName="@FogDensity")
	float FogDensity{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@FogHeightFalloff")
	float FogHeightFalloff{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@SecondFogDensity")
	float SecondFogDensity{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@SecondFogHeightFalloff")
	float SecondFogHeightFalloff{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@SecondFogHeightOffset")
	float SecondFogHeightOffset{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@FogMaxOpacity")
	float FogMaxOpacity{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@FogInscatteringColor")
	FLinearColor FogInscatteringColor{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@HiddenInGame")
	bool bVolumetricFog{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@HiddenInGame")
	bool bHiddenInGame{};
	
	FU5_WeatherHeightFog_Struct() = default;

	void ResetWeatherHeightFogData()
	{
		FogDensity = 0.0f;
		FogHeightFalloff = 0.0f;
		SecondFogDensity = 0.0f;
		SecondFogHeightFalloff = 0.0f;
		SecondFogHeightOffset = 0.0f;
		FogMaxOpacity = 0.0f;
		FogInscatteringColor = FLinearColor::White;
		bVolumetricFog = false;
		bHiddenInGame = false;
	}
};


USTRUCT(BlueprintType)
struct FU5_WeatherData_Struct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, DisplayName="@WeatherShadowsLightData")
	FU5_WeatherLightData_Struct WeatherShadowsLightData{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@WeatherNoShadowsLightData")
	FU5_WeatherLightData_Struct WeatherNoShadowsLightDatas{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@WeatherShadowColorData")
	FU5_WeatherShadowColorData_Struct WeatherShadowColorData{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@WeatherParticles")
	UNiagaraComponent* WeatherParticles;
	UPROPERTY(BlueprintReadWrite, DisplayName="@WeatherFogData")
	FU5_WeatherHeightFog_Struct WeatherFogData{};
	UPROPERTY(BlueprintReadWrite, DisplayName="@IsValid")
	bool bIsValid;
	
	FU5_WeatherData_Struct() = default;
	void ResetWeatherData()
	{
		bIsValid = false;
		WeatherShadowsLightData.ResetLightData();
		WeatherNoShadowsLightDatas.ResetLightData();
		WeatherShadowColorData.ResetShadowColorData();
		WeatherFogData.ResetWeatherHeightFogData();
		WeatherParticles = nullptr;
	}
};
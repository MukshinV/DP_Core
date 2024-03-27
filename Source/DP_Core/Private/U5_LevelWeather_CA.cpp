// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_LevelWeather_CA.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SkyLightComponent.h"
#include "NiagaraComponent.h"
#include "Controller/U5_Behavior_ACC.h"
#include "UnrealCore/U5_GameInstace.h"
#include "Utils/U5_Utils.h"
#include "WeatherSystem/U5_WeatherSource_CI.h"


AU5_LevelWeather_CA::AU5_LevelWeather_CA()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(L"Scene");
	sceneComponent->SetupAttachment(RootComponent);

	DirectionalLightNoShadow = CreateDefaultSubobject<UDirectionalLightComponent>(L"DirLightNoShadow");
	DirectionalLightNoShadow->SetupAttachment(sceneComponent);
	DirectionalLightWithShadow = CreateDefaultSubobject<UDirectionalLightComponent>(L"DirLightWithShadow");
	DirectionalLightWithShadow->SetupAttachment(sceneComponent);
	SkyLight = CreateDefaultSubobject<USkyLightComponent>(L"SkyLight");
	SkyLight->SetupAttachment(sceneComponent);
	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(L"PostProcess");
	PostProcess->SetupAttachment(sceneComponent);
	ExponentialHeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(L"ExponentialHeightFog");
	ExponentialHeightFog->SetupAttachment(sceneComponent);

	_weatherInterpolationValue = 1.0f;
}

void AU5_LevelWeather_CA::InterpolateDirLightWithShadow()
{
	const float targetIntensity = FMath::Lerp(PreviousWeatherData.WeatherShadowsLightData.Intensity, CurrentWeatherData.WeatherShadowsLightData.Intensity, _weatherInterpolationValue);
	const FRotator targetRotator = FMath::Lerp(PreviousWeatherData.WeatherShadowsLightData.LightWorldRotation, CurrentWeatherData.WeatherShadowsLightData.LightWorldRotation, _weatherInterpolationValue);
	const FLinearColor targetColor = FMath::Lerp(PreviousWeatherData.WeatherShadowsLightData.LightColor, CurrentWeatherData.WeatherShadowsLightData.LightColor, _weatherInterpolationValue);
	
	DirectionalLightWithShadow->SetIntensity(targetIntensity);
	DirectionalLightWithShadow->SetWorldRotation(targetRotator);
	DirectionalLightWithShadow->SetLightColor(targetColor);
}

void AU5_LevelWeather_CA::InterpolateDirLightNoShadow()
{
	const float targetIntensity = FMath::Lerp(PreviousWeatherData.WeatherNoShadowsLightDatas.Intensity, CurrentWeatherData.WeatherNoShadowsLightDatas.Intensity, _weatherInterpolationValue);
	const FRotator targetRotator = FMath::Lerp(PreviousWeatherData.WeatherNoShadowsLightDatas.LightWorldRotation, CurrentWeatherData.WeatherNoShadowsLightDatas.LightWorldRotation, _weatherInterpolationValue);
	const FLinearColor targetColor = FMath::Lerp(PreviousWeatherData.WeatherNoShadowsLightDatas.LightColor, CurrentWeatherData.WeatherNoShadowsLightDatas.LightColor, _weatherInterpolationValue);
	
	DirectionalLightNoShadow->SetIntensity(targetIntensity);
	DirectionalLightNoShadow->SetWorldRotation(targetRotator);
	DirectionalLightNoShadow->SetLightColor(targetColor);
}

void AU5_LevelWeather_CA::InterpolateExpFog()
{
	//???
	ExponentialHeightFog->SetHiddenInGame(CurrentWeatherData.WeatherFogData.bHiddenInGame);
	ExponentialHeightFog->SetVolumetricFog(CurrentWeatherData.WeatherFogData.bVolumetricFog);

	const float targetFogDensity = FMath::Lerp(PreviousWeatherData.WeatherFogData.FogDensity, CurrentWeatherData.WeatherFogData.FogDensity, _weatherInterpolationValue);
	const float targetHeightFalloff = FMath::Lerp(PreviousWeatherData.WeatherFogData.FogHeightFalloff, CurrentWeatherData.WeatherFogData.FogHeightFalloff, _weatherInterpolationValue);
	const float targetFogMaxOpacity = FMath::Lerp(PreviousWeatherData.WeatherFogData.FogMaxOpacity, CurrentWeatherData.WeatherFogData.FogMaxOpacity, _weatherInterpolationValue);
	const FLinearColor targetInscatteringLuminance = FMath::Lerp(PreviousWeatherData.WeatherFogData.FogInscatteringColor, CurrentWeatherData.WeatherFogData.FogInscatteringColor, _weatherInterpolationValue);
	const float targetSecondFogDensity = FMath::Lerp(PreviousWeatherData.WeatherFogData.SecondFogDensity, CurrentWeatherData.WeatherFogData.SecondFogDensity, _weatherInterpolationValue);
	const float targetSecondFogHeightFalloff = FMath::Lerp(PreviousWeatherData.WeatherFogData.SecondFogHeightFalloff, CurrentWeatherData.WeatherFogData.SecondFogHeightFalloff, _weatherInterpolationValue);
	const float targetSecondFogHeightOffset = FMath::Lerp(PreviousWeatherData.WeatherFogData.SecondFogHeightOffset, CurrentWeatherData.WeatherFogData.SecondFogHeightOffset, _weatherInterpolationValue);

	ExponentialHeightFog->SetFogDensity(targetFogDensity);
	ExponentialHeightFog->SetFogHeightFalloff(targetHeightFalloff);
	ExponentialHeightFog->SetFogInscatteringColor(targetInscatteringLuminance);
	ExponentialHeightFog->SetFogMaxOpacity(targetFogMaxOpacity);
	ExponentialHeightFog->SetSecondFogDensity(targetSecondFogDensity);
	ExponentialHeightFog->SetSecondFogHeightFalloff(targetSecondFogHeightFalloff);
	ExponentialHeightFog->SetSecondFogHeightOffset(targetSecondFogHeightOffset);
}

void AU5_LevelWeather_CA::SetFXVisibility_Implementation(bool _isVisible)
{
	DirectionalLightWithShadow->SetVisibility(_isVisible);
	DirectionalLightNoShadow->SetVisibility(_isVisible);
	ExponentialHeightFog->SetVisibility(_isVisible);
}

void AU5_LevelWeather_CA::InterpolateParticles() const
{
	const UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(GetGameInstance());
	if(!gameInstance) return;
	if(!gameInstance->LocalController) return;
	UU5_Behavior_ACC* behaviour = gameInstance->LocalController->GetPawn()->FindComponentByClass<UU5_Behavior_ACC>();
	if(!behaviour) return;

	behaviour->SetCurrentParticles(CurrentWeatherData.WeatherParticles);
}

void AU5_LevelWeather_CA::InterpolateSkyLight() const
{
	SkyLight->SetCastShadows(CurrentWeatherData.WeatherShadowColorData.bCastShadows);
	
	const float targetSkyIntensity = FMath::Lerp(PreviousWeatherData.WeatherShadowColorData.Intensity, CurrentWeatherData.WeatherShadowColorData.Intensity, _weatherInterpolationValue);
	const float targetSkySourceCubemapAngle = FMath::Lerp(PreviousWeatherData.WeatherShadowColorData.SourceCubemapAngle, CurrentWeatherData.WeatherShadowColorData.SourceCubemapAngle, _weatherInterpolationValue);
	const float targetSkyVolumetricScatteringIntensity = FMath::Lerp(PreviousWeatherData.WeatherShadowColorData.VolumetricScatteringIntensity, CurrentWeatherData.WeatherShadowColorData.VolumetricScatteringIntensity, _weatherInterpolationValue);
	
	SkyLight->SetIntensity(targetSkyIntensity);
	SkyLight->SetSourceCubemapAngle(targetSkySourceCubemapAngle);
	SkyLight->SetVolumetricScatteringIntensity(targetSkyVolumetricScatteringIntensity);
}

void AU5_LevelWeather_CA::InterpolateWeatherData()
{
	InterpolateDirLightNoShadow();
	InterpolateDirLightWithShadow();
	InterpolateExpFog();
	InterpolateSkyLight();
	InterpolateParticles();
}

void AU5_LevelWeather_CA::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	_weatherInterpolationValue += DeltaSeconds;
	_weatherInterpolationValue = FMath::Min(1.0f, _weatherInterpolationValue);
	
	InterpolateWeatherData();

	if(FMath::IsNearlyEqual(1.0f, _weatherInterpolationValue))
	{
		SetActorTickEnabled(false);
	}
}

void AU5_LevelWeather_CA::SetWeatherSource_Implementation(AActor* _sourceActor)
{
	if(!_sourceActor) return;

	SetFXVisibility(true);

	LocalWeatherSource = _sourceActor;
	mU5_DEBUGOUT(true, L"New level weather " << mDNAME(LocalWeatherSource))

	IU5_WeatherSource_CI* weatherSourceInterface = Cast<IU5_WeatherSource_CI>(LocalWeatherSource);
	if(!weatherSourceInterface) return;

	PreviousWeatherData = CurrentWeatherData;
	CurrentWeatherData = weatherSourceInterface->Execute_GetWeatherData(LocalWeatherSource);

	if(!PreviousWeatherData.bIsValid)
	{
		_weatherInterpolationValue = 1.0f;
		InterpolateWeatherData();
		return;
	}

	_weatherInterpolationValue = 0.0f;
	SetActorTickEnabled(true);
}

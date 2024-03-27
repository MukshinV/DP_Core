#include "WeatherSystem/U5_AreaWeather_CA.h"

#include "U5_LevelWeather_CA.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyLightComponent.h"
#include "Controller/U5_Behavior_ACC.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealCore/U5_GameInstace.h"

AU5_AreaWeather_CA::AU5_AreaWeather_CA()
{
	PrimaryActorTick.bCanEverTick = false;
}

#if WITH_EDITOR

void AU5_AreaWeather_CA::MakeActive()
{
	Super::MakeActive();

	AActor* levelWeather = UGameplayStatics::GetActorOfClass(this, AU5_LevelWeather_CA::StaticClass());
	if(levelWeather)
	{
		Cast<AU5_LevelWeather_CA>(levelWeather)->SetFXVisibility(false);
	}
}

void AU5_AreaWeather_CA::SwitchOff()
{
	Super::SwitchOff();

	AActor* levelWeather = UGameplayStatics::GetActorOfClass(this, AU5_LevelWeather_CA::StaticClass());
	if(levelWeather)
	{
		Cast<AU5_LevelWeather_CA>(levelWeather)->SetFXVisibility(true);
	}
}

#endif

void AU5_AreaWeather_CA::BeginPlay()
{
	Super::BeginPlay();

	CollectWeatherData();
}

void AU5_AreaWeather_CA::ProcessDirectionalLights()
{
	TArray<UDirectionalLightComponent*> directionalLights;
	GetComponents<UDirectionalLightComponent>(directionalLights);

	for (int32 i = 0; i < directionalLights.Num(); ++i)
	{
		const UDirectionalLightComponent* dirLight = directionalLights[i];

		FU5_WeatherLightData_Struct lightData{};

		lightData.Intensity = dirLight->Intensity;
		lightData.LightWorldRotation = dirLight->GetComponentRotation();
		lightData.LightColor = dirLight->LightColor;
		lightData.bCastShadows = dirLight->CastShadows;

		if(lightData.bCastShadows)
		{
			WeatherData.WeatherShadowsLightData = lightData;
		}
		else
		{
			WeatherData.WeatherNoShadowsLightDatas = lightData;
		}
	}
}

void AU5_AreaWeather_CA::ProcessExponentialFogs()
{
	TArray<UActorComponent*> foundFogs = GetComponentsByTag(UExponentialHeightFogComponent::StaticClass(), FName{L"!AreaHeightFog"});

	for (int32 i = 0; i < foundFogs.Num(); ++i)
	{
		UExponentialHeightFogComponent* fog = Cast<UExponentialHeightFogComponent>(foundFogs[i]);

		WeatherData.WeatherFogData.bHiddenInGame = fog->bHiddenInGame;
		WeatherData.WeatherFogData.bVolumetricFog = fog->bEnableVolumetricFog;
		WeatherData.WeatherFogData.FogDensity = fog->FogDensity;
		WeatherData.WeatherFogData.FogHeightFalloff = fog->FogHeightFalloff;
		WeatherData.WeatherFogData.FogInscatteringColor = fog->FogInscatteringLuminance;
		WeatherData.WeatherFogData.FogMaxOpacity = fog->FogMaxOpacity;
		WeatherData.WeatherFogData.SecondFogDensity = fog->SecondFogData.FogDensity;
		WeatherData.WeatherFogData.SecondFogHeightFalloff = fog->SecondFogData.FogHeightFalloff;
		WeatherData.WeatherFogData.SecondFogHeightOffset = fog->SecondFogData.FogHeightOffset;
	}
}

void AU5_AreaWeather_CA::ProcessParticles()
{
	TArray<UActorComponent*> foundParticles = GetComponentsByTag(UNiagaraComponent::StaticClass(), FName{L"!LocalPlayerSystem"});

	for (int32 i = 0; i < foundParticles.Num(); ++i)
	{
		UNiagaraComponent* particle = Cast<UNiagaraComponent>(foundParticles[i]);
		WeatherData.WeatherParticles = particle;
	}
}

void AU5_AreaWeather_CA::ProcessSkyLight()
{
	TArray<UActorComponent*> foundSkylights = GetComponentsByTag(USkyLightComponent::StaticClass(), FName{L"!ShadowColor"});

	for (int32 i = 0; i < foundSkylights.Num(); ++i)
	{
		const USkyLightComponent* incomingSkylight = Cast<USkyLightComponent>(foundSkylights[i]);

		WeatherData.WeatherShadowColorData.Intensity = incomingSkylight->Intensity;
		WeatherData.WeatherShadowColorData.SourceCubemapAngle = incomingSkylight->SourceCubemapAngle;
		WeatherData.WeatherShadowColorData.bCastShadows = incomingSkylight->CastShadows;
		WeatherData.WeatherShadowColorData.VolumetricScatteringIntensity = incomingSkylight->VolumetricScatteringIntensity;
	}
}

void AU5_AreaWeather_CA::CollectWeatherData_Implementation()
{
	WeatherData.ResetWeatherData();

	ProcessDirectionalLights();
	ProcessExponentialFogs();
	ProcessParticles();
	ProcessSkyLight();

	WeatherData.bIsValid = true;
}


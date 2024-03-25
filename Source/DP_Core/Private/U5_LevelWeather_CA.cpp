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


AU5_LevelWeather_CA::AU5_LevelWeather_CA()
{
	PrimaryActorTick.bCanEverTick = false;

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
}

void AU5_LevelWeather_CA::ApplyDirLightWithShadow(const ULightComponent* _lightComponent)
{
	DirectionalLightWithShadow->SetIntensity(_lightComponent->Intensity);
	DirectionalLightWithShadow->SetWorldRotation(_lightComponent->GetComponentRotation());
	DirectionalLightWithShadow->SetLightColor(_lightComponent->LightColor);
}

void AU5_LevelWeather_CA::ApplyDirLightNoShadow(const ULightComponent* _lightComponent)
{
	DirectionalLightNoShadow->SetIntensity(_lightComponent->Intensity);
	DirectionalLightNoShadow->SetWorldRotation(_lightComponent->GetComponentRotation());
	DirectionalLightNoShadow->SetLightColor(_lightComponent->LightColor);
}

void AU5_LevelWeather_CA::ApplyExpFog()
{
	if(TargetFog->bHiddenInGame)
	{
		ExponentialHeightFog->SetHiddenInGame(true);
	}
	else
	{
		ExponentialHeightFog->SetHiddenInGame(false);
		ExponentialHeightFog->SetFogDensity(TargetFog->FogDensity);
		ExponentialHeightFog->SetFogHeightFalloff(TargetFog->FogHeightFalloff);
	}

	ExponentialHeightFog->SetSecondFogDensity(TargetFog->SecondFogData.FogDensity);
	ExponentialHeightFog->SetSecondFogHeightFalloff(TargetFog->SecondFogData.FogHeightFalloff);
	ExponentialHeightFog->SetSecondFogHeightOffset(TargetFog->SecondFogData.FogHeightOffset);

	ExponentialHeightFog->SetFogInscatteringColor(TargetFog->FogInscatteringLuminance);
	ExponentialHeightFog->SetVolumetricFog(TargetFog->bEnableVolumetricFog);
	ExponentialHeightFog->SetFogMaxOpacity(TargetFog->FogMaxOpacity);
}

void AU5_LevelWeather_CA::SetFXVisibility(bool _isVisible)
{
	DirectionalLightWithShadow->SetVisibility(_isVisible);
	DirectionalLightNoShadow->SetVisibility(_isVisible);
	ExponentialHeightFog->SetVisibility(_isVisible);
}

void AU5_LevelWeather_CA::ProcessDirectionalLights()
{
	TArray<UDirectionalLightComponent*> directionalLights;
	LocalWeatherSource->GetComponents<UDirectionalLightComponent>(directionalLights);

	for (int32 i = 0; i < directionalLights.Num(); ++i)
	{
		UDirectionalLightComponent* dirLight = directionalLights[i];
		if(dirLight->CastShadows)
		{
			ApplyDirLightWithShadow(dirLight);
			continue;
		}

		ApplyDirLightNoShadow(dirLight);
	}
}

void AU5_LevelWeather_CA::ProcessExponentialFogs()
{
	TArray<UActorComponent*> foundFogs = LocalWeatherSource->GetComponentsByTag(UExponentialHeightFogComponent::StaticClass(), FName{L"!AreaHeightFog"});

	for (int32 i = 0; i < foundFogs.Num(); ++i)
	{
		UExponentialHeightFogComponent* fog = Cast<UExponentialHeightFogComponent>(foundFogs[i]);
		TargetFog = fog;
	}

	ApplyExpFog();
}

void AU5_LevelWeather_CA::ProcessParticles() const
{
	const UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(GetGameInstance());
	if(!gameInstance) return;
	if(!gameInstance->LocalController) return;
	UU5_Behavior_ACC* behaviour = gameInstance->LocalController->GetPawn()->FindComponentByClass<UU5_Behavior_ACC>();
	if(!behaviour) return;
	
	TArray<UActorComponent*> foundParticles = LocalWeatherSource->GetComponentsByTag(UNiagaraComponent::StaticClass(), FName{L"!LocalPlayerSystem"});

	for (int32 i = 0; i < foundParticles.Num(); ++i)
	{
		UNiagaraComponent* particle = Cast<UNiagaraComponent>(foundParticles[i]);
		behaviour->SetCurrentParticles(particle);
	}
}

void AU5_LevelWeather_CA::ProcessSkyLight()
{
	TArray<UActorComponent*> foundSkylights = LocalWeatherSource->GetComponentsByTag(USkyLightComponent::StaticClass(), FName{L"!ShadowColor"});

	for (int32 i = 0; i < foundSkylights.Num(); ++i)
	{
		const USkyLightComponent* incomingSkylight = Cast<USkyLightComponent>(foundSkylights[i]);

		SkyLight->SetIntensity(incomingSkylight->Intensity);
		SkyLight->SetSourceCubemapAngle(incomingSkylight->SourceCubemapAngle);
		SkyLight->SetCastShadows(incomingSkylight->CastShadows);
		SkyLight->SetVolumetricScatteringIntensity(incomingSkylight->VolumetricScatteringIntensity);
	}
}

void AU5_LevelWeather_CA::SetWeatherSource_Implementation(AActor* _sourceActor)
{
	if(!_sourceActor) return;

	SetFXVisibility(true);
	LocalWeatherSource = _sourceActor;

	mU5_DEBUGOUT(true, L"New level weather " << mDNAME(LocalWeatherSource))
	
	ProcessDirectionalLights();
	ProcessExponentialFogs();
	ProcessParticles();
	ProcessSkyLight();
}

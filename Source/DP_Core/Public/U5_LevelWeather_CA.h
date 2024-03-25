// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_LevelActor_CA.h"
#include "GameFramework/Actor.h"
#include "U5_LevelWeather_CA.generated.h"

UCLASS()
class DP_CORE_API AU5_LevelWeather_CA : public AU5_LevelActor_CA
{
	GENERATED_BODY()

public:
	AU5_LevelWeather_CA();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!SetWeatherSourceC")
	void SetWeatherSource(AActor* _sourceActor);

	UFUNCTION(BlueprintCallable, DisplayName="!ApplyDirLightWithShadow(C, Virtual)(LightComponent)")
	virtual void ApplyDirLightWithShadow(const class ULightComponent* _lightComponent);
	UFUNCTION(BlueprintCallable, DisplayName="!ApplyDirLightNoShadow(C, Virtual)(LightComponent)")
	virtual void ApplyDirLightNoShadow(const ULightComponent* _lightComponent);
	UFUNCTION(BlueprintCallable, DisplayName="!ApplyExpFog(C, Virtual)")
	virtual void ApplyExpFog();
	UFUNCTION(BlueprintCallable, DisplayName="!SetFXVisibility(C, Virtual)(bool)")
	virtual void SetFXVisibility(bool _isVisible);

	void ProcessDirectionalLights();
	void ProcessExponentialFogs();
	void ProcessParticles() const;
	void ProcessSkyLight();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@LocalWeatherSource")
	TObjectPtr<AActor> LocalWeatherSource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@TargetFog")
	TObjectPtr<class UExponentialHeightFogComponent> TargetFog;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@DirectionalLightNoShadow")
	TObjectPtr<class UDirectionalLightComponent> DirectionalLightNoShadow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@DirectionalLightNoShadow")
	TObjectPtr<UDirectionalLightComponent> DirectionalLightWithShadow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@SkyLight")
	TObjectPtr<class USkyLightComponent> SkyLight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@PostProcess")
	TObjectPtr<class UPostProcessComponent> PostProcess;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@ExponentialHeightFog")
	TObjectPtr<class UExponentialHeightFogComponent> ExponentialHeightFog;
};

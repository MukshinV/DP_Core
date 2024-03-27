// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_LevelActor_CA.h"
#include "GameFramework/Actor.h"
#include "WeatherSystem/U5_WeatherSystemTypes.h"
#include "U5_LevelWeather_CA.generated.h"

USTRUCT()
struct FU5_WeatherInterpolator_Struct
{
	GENERATED_BODY()
public:
	
};

UCLASS()
class DP_CORE_API AU5_LevelWeather_CA : public AU5_LevelActor_CA
{
	GENERATED_BODY()

public:
	AU5_LevelWeather_CA();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!SetWeatherSourceC")
	void SetWeatherSource(AActor* _sourceActor);

	UFUNCTION(BlueprintCallable, DisplayName="!InterpolateDirLightWithShadow(C, Virtual)(LightComponent)")
	virtual void InterpolateDirLightWithShadow();
	UFUNCTION(BlueprintCallable, DisplayName="!InterpolateDirLightNoShadow(C, Virtual)(LightComponent)")
	virtual void InterpolateDirLightNoShadow();
	UFUNCTION(BlueprintCallable, DisplayName="!InterpolateExpFog(C, Virtual)")
	virtual void InterpolateExpFog();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!SetFXVisibilityC")
	void SetFXVisibility(bool _isVisible);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@LocalWeatherSource")
	TObjectPtr<AActor> LocalWeatherSource;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@DirectionalLightNoShadow")
	TObjectPtr<class UDirectionalLightComponent> DirectionalLightNoShadow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@DirectionalLightWithShadow")
	TObjectPtr<UDirectionalLightComponent> DirectionalLightWithShadow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@SkyLight")
	TObjectPtr<class USkyLightComponent> SkyLight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@PostProcess")
	TObjectPtr<class UPostProcessComponent> PostProcess;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName="@ExponentialHeightFog")
	TObjectPtr<class UExponentialHeightFogComponent> ExponentialHeightFog;

	void InterpolateParticles() const;
	void InterpolateSkyLight() const;
	void InterpolateWeatherData();
	
	virtual void Tick(float DeltaSeconds) override;
	
private:
	FU5_WeatherData_Struct CurrentWeatherData{};
	FU5_WeatherData_Struct PreviousWeatherData{};
	
	float _weatherInterpolationValue{1.0f};
};

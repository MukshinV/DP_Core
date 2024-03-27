
#pragma once

#include "CoreMinimal.h"
#include "U5_WeatherSource_CI.h"
#include "EventSystem/U5_AreaEvent_CA.h"
#include "U5_AreaWeather_CA.generated.h"

UCLASS(Blueprintable)
class DP_CORE_API AU5_AreaWeather_CA : public AU5_AreaEvent_CA, public IU5_WeatherSource_CI
{
	GENERATED_BODY()
public:
	AU5_AreaWeather_CA();

#if WITH_EDITOR
	virtual void MakeActive() override;
	virtual void SwitchOff() override;
#endif

	virtual FU5_WeatherData_Struct GetWeatherData_Implementation() const override { return WeatherData; }

protected:
	UPROPERTY(BlueprintReadWrite, DisplayName="@WeatherData")
	FU5_WeatherData_Struct WeatherData;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!CollectWeatherData(C, Virtual)")
	void CollectWeatherData();
	
	virtual void BeginPlay() override;

	void ProcessDirectionalLights();
	void ProcessExponentialFogs();
	void ProcessParticles();
	void ProcessSkyLight();
};

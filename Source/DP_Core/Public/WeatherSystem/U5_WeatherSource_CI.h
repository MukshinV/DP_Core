// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "U5_WeatherSystemTypes.h"
#include "U5_WeatherSource_CI.generated.h"

UINTERFACE()
class UU5_WeatherSource_CI : public UInterface
{
	GENERATED_BODY()
};

class DP_CORE_API IU5_WeatherSource_CI
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="GetWeatherData(Interface)")
	FU5_WeatherData_Struct GetWeatherData() const;
};

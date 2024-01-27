// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_TemperatureController_CA.h"


AU5_TemperatureController_CA::AU5_TemperatureController_CA()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AU5_TemperatureController_CA::UpdateSource(const FString& _sourceName, float _currentTemperature)
{
	FU5_TemperatureSource_Struct* foundTemperatureValue = CurrentSources.Find(_sourceName);

	if(foundTemperatureValue)
	{
		*foundTemperatureValue = FU5_TemperatureSource_Struct{_currentTemperature};
		return;
	}

	CurrentSources.Add(_sourceName, FU5_TemperatureSource_Struct{_currentTemperature});
}

float AU5_TemperatureController_CA::CalculateTotalTemperature() const
{
	float totalTemperature = DefaultTemperature;
	
	for(const TTuple<FString, FU5_TemperatureSource_Struct>& _pair : CurrentSources)
	{
		const float sourceTemperature = _pair.Value.SourceTemperature; 
		const float temperatureDelta = sourceTemperature - DefaultTemperature;
		totalTemperature += temperatureDelta;
	}
	
	return totalTemperature;
}



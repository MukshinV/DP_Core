// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_TemperatureProcessor.h"

#include "Utils/U5_Utils.h"

void UU5_TemperatureProcessor::SetTemperatureParameters(const FU5_TemperatureSourceParameters_Struct& _sourceParameters)
{
	SourceParameters = _sourceParameters;
}

void UU5_TemperatureProcessor::StartUpTemperature()
{
	TemperatureLerper.ResetRatio();
	TemperatureLerper.SetFromValue(OutdoorTemperature);
	TemperatureLerper.SetToValue(SourceParameters.TargetTemperature);
	mU5_DEBUGOUT(true, "Start up temperature from: " << OutdoorTemperature << " to " << SourceParameters.TargetTemperature);
}

void UU5_TemperatureProcessor::StartDownTemperature()
{
	TemperatureLerper.ResetRatio();
	TemperatureLerper.SetFromValue(SourceParameters.TargetTemperature);
	TemperatureLerper.SetToValue(OutdoorTemperature);
	mU5_DEBUGOUT(true, "Start down temperature from: " << SourceParameters.TargetTemperature << " to " << OutdoorTemperature);
}

float UU5_TemperatureProcessor::GetCurrentTemperature() const
{
	return FMath::Lerp(*TemperatureLerper.FromValue, *TemperatureLerper.ToValue,  TemperatureCurve->GetFloatValue(TemperatureLerper.Ratio));
}

void UU5_TemperatureProcessor::UpdateTemperature(float _deltaSeconds)
{
	TemperatureLerper.AddRatioValue(_deltaSeconds * SourceParameters.TemperatureSpeed);
}

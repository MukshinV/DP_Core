// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_TemperatureController_CA.h"
#include "UObject/Object.h"
#include "U5_TemperatureProcessor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DP_CORE_API UU5_TemperatureProcessor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="!IsTemperatureProcessingFinished(C)")
	bool IsTemperatureProcessingFinished() const { return TemperatureLerper.Ratio >= 0.999f; }
	UFUNCTION(BlueprintCallable, DisplayName="!SetTemperatureParameters(C)(float)")
	void SetTemperatureParameters(const FU5_TemperatureSourceParameters_Struct& _sourceParameters);
	UFUNCTION(BlueprintCallable, DisplayName="!StartUpTemperature(C)")
	void StartUpTemperature();
	UFUNCTION(BlueprintCallable, DisplayName="!StartDownTemperature(C)")
	void StartDownTemperature();
	UFUNCTION(BlueprintCallable, DisplayName="!GetCurrentTemperature(C)")
	float GetCurrentTemperature() const;
	UFUNCTION(BlueprintCallable, DisplayName="!UpdateTemperature(C)(float)")
	void UpdateTemperature(float _deltaSeconds);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="@TemperatureCurve")
	TObjectPtr<UCurveFloat> TemperatureCurve;
private:
	FU5_TemperatureSourceParameters_Struct SourceParameters;
	float OutdoorTemperature{ 0.0f };
	
	struct TemperatureLerper
	{
		float FromValue;
		float ToValue;
		float Ratio{1.0f};
		
		void SetFromValue(float _fromValue) { FromValue = _fromValue; }
		void SetToValue(float _toValue) { ToValue = _toValue; }
		void AddRatioValue(float _addValue) { Ratio = FMath::Min(1.0f, Ratio + _addValue); };
		void ResetRatio() { Ratio = 1.0f - Ratio; }
	} TemperatureLerper;
};

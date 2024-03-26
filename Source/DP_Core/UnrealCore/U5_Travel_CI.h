// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "U5_Travel_CI.generated.h"

UINTERFACE()
class UU5_Travel_CI : public UInterface
{
	GENERATED_BODY()
};

class DP_CORE_API IU5_Travel_CI
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="TravelTo(Interface)")
	void TravelTo(const FDataTableRowHandle& _levelToGo);
};

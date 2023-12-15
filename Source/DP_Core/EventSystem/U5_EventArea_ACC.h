// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_Event_ACC.h"
#include "U5_EventArea_ACC.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DP_CORE_API UU5_EventArea_ACC : public UU5_Event_ACC
{
	GENERATED_BODY()
public:
	UPROPERTY(DisplayName="@BehaviorsCount")
	int32 BehaviorsEnteredCount;

	class UU5_Behavior_ACC;
	UPROPERTY(DisplayName="@BehaviorsArray")
	TArray<UU5_Behavior_ACC*> BehaviorsEnteredArray;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_EventSystem_ACC.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "U5_Event_BlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DP_CORE_API UU5_Event_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//! Only a true way to convert handle to string for all project.
	UFUNCTION(BlueprintCallable, DisplayName="?EventHandleToString(C)(FString, FDataTableRowHandle)")
	static void EventHandleToString(FString& _result, const FDataTableRowHandle& _handle);

	UFUNCTION(BlueprintCallable, DisplayName="?SetEventValue(C)(World, FString, float, bool, bool)")
	static void SetEventValue(const UWorld* _world, const FString& _eventName, float _eventValue, bool _bEvenIsDisabled = false, bool _bEvenIfAlreadySet = false);

	UFUNCTION(BlueprintCallable, DisplayName="?TryGetEventValue(C)(World, FString)")
	static bool TryGetEventValue(const UWorld* _world, const FString& _eventName, float& _eventValue);

	UFUNCTION(BlueprintCallable, DisplayName="?IsEventDisabled(C)(World, FString)")
	static bool IsEventDisabled(const UWorld* _world, const FString& _eventName);

private:
	static UU5_EventSystem_ACC* GetEventSystem(const UWorld* _world);
};


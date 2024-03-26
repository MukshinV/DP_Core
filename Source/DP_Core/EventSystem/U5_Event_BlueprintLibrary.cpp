// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_Event_BlueprintLibrary.h"

#include "U5_EventSystem_ACC.h"
#include "GameFramework/GameModeBase.h"
#include "Utils/U5_Utils.h"

void UU5_Event_BlueprintLibrary::EventHandleToString(FString& _result, const FDataTableRowHandle& _handle)
{
	_result = (_handle.DataTable.GetName() + " : " + _handle.RowName.ToString());
}

void UU5_Event_BlueprintLibrary::SetEventValue(const UWorld* _world, const FString& _eventName, float _eventValue, bool _bEvenIsDisabled, bool _bEvenIfAlreadySet)
{
	float currentEventValue = 0.0f;
	if(!TryGetEventValue(_world, _eventName, currentEventValue))
	{
		mU5_DEBUGOUT(true, L"Unable to set event: " << _eventName << ". Event is not found in system");
		return;
	}

	if(IsEventDisabled(_world, _eventName) || _bEvenIsDisabled) return;
	if(FMath::IsNearlyEqual(_eventValue, currentEventValue) || _bEvenIfAlreadySet) return;

	UU5_EventSystem_ACC* foundEventSystem = GetEventSystem(_world);
	if(!foundEventSystem) return;

	foundEventSystem->SetEventValueS(_eventName, _eventValue);

	mU5_DEBUGOUT(true, L"Set Event Value: " << _eventName << L" : " << _eventValue);
}

bool UU5_Event_BlueprintLibrary::TryGetEventValue(const UWorld* _world, const FString& _eventName, float& _eventValue)
{
	UU5_EventSystem_ACC* foundEventSystem = GetEventSystem(_world);
	if(!foundEventSystem) return false;

	_eventValue = foundEventSystem->GetEventValueS(_eventName);
	return true;
}

bool UU5_Event_BlueprintLibrary::IsEventDisabled(const UWorld* _world, const FString& _eventName)
{
	float eventValue = 0.0f;
	if(!TryGetEventValue(_world, _eventName, eventValue)) return true;

	return FMath::IsNearlyEqual(eventValue, -1.0f);
}

UU5_EventSystem_ACC* UU5_Event_BlueprintLibrary::GetEventSystem(const UWorld* _world)
{
	if(!_world) return nullptr;
	
	const AGameModeBase* gameMode = _world->GetAuthGameMode();
	if(!gameMode) return nullptr;

	return gameMode->FindComponentByClass<UU5_EventSystem_ACC>();
}


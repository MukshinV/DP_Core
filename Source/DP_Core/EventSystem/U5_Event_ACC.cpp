// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_Event_ACC.h"
#include "U5_EventSystem_ACC.h"

void UU5_Event_ACC::BeginPlay()
{
	Super::BeginPlay();
	if (UU5_EventSystem_ACC* eventSystem = TryGetEventSystem())
	{
		eventSystem->RegisterEvent(this);
	}
}

void UU5_Event_ACC::BeginDestroy()
{
	//OnEventChanged_Delegate.Clear();
	Super::BeginDestroy();
}

void UU5_Event_ACC::EndPlay(const EEndPlayReason::Type _reason)
{
	if (UU5_EventSystem_ACC* eventSystem = TryGetEventSystem())
	{
		eventSystem->UnRegisterEvent(this);
	}
	Super::EndPlay(_reason);
}


void UU5_Event_ACC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UU5_EventSystem_ACC* UU5_Event_ACC::TryGetEventSystem()
{
	if (UWorld* const world = GetWorld())
	{
		AActor* gameMode = (AActor*)world->GetAuthGameMode();
		if (!gameMode) return nullptr; // Authority failed.

		return Cast<UU5_EventSystem_ACC>(gameMode->FindComponentByClass<UU5_EventSystem_ACC>());
	}
	// Level travel.
	return nullptr;
}

void UU5_Event_ACC::SetEventValue(const FString& _event, float _value)
{
	this->Value = _value;
	OnEventChanged_Delegate.Broadcast(_event, _value, this);
}
// Fill out your copyright notice in the Description page of Project Settings.
#include "U5_EventSystem_ACC.h"
#include "U5_Event_ACC.h"

#include "../Utils/U5_Utils.h"

#include "GameFramework/GameMode.h"

void UU5_EventSystem_ACC::BeginPlay()
{
	Super::BeginPlay();
	CheckParent_Internal();

	GetWorld()->GetTimerManager().SetTimerForNextTick( 
		[this] ()
		{
			mU5_DEBUGOUT(false, "Saves loaded");
			EventSystemData.IsSavesLoaded = true; 
		}
	);
}

void UU5_EventSystem_ACC::OnComponentCreated()
{
	Super::OnComponentCreated();
	EventSystemData.NewEventDelegate = &OnNewEventRegistred;
}

// Called every frame
void UU5_EventSystem_ACC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UU5_EventSystem_ACC::CheckParent_Internal()
{
	check(Cast<AGameModeBase>(GetOwner()));
}

void UU5_EventSystem_ACC::EventHandleToString(FString& _result, const FDataTableRowHandle& _handle)
{
	_result = (_handle.DataTable.GetName() + " : " + _handle.RowName.ToString());
}

void UU5_EventSystem_ACC::RegisterEvent(const UU5_Event_ACC* _event)
{
	check(_event);
	mU5_FUNCMESS(false, _event->GetReadableName());
	EventSystemData.AddEvent(const_cast<UU5_Event_ACC*>(_event));
}

void UU5_EventSystem_ACC::UnRegisterEvent(const UU5_Event_ACC* _event)
{
	check(_event);
	mU5_FUNCMESS(false, _event->GetReadableName());
	UU5_Event_ACC* event = const_cast<UU5_Event_ACC*>(_event);
	for (FDataTableRowHandle& _handle : event->ResponceList)
	{
		FString eventTag; EventHandleToString(eventTag, _handle);
		FEventHandlers* _handlers =  EventSystemData.GetEvents().Find(eventTag);
		if (_handlers)
		{
			int32 element = _handlers->Events.Find(event);
			if(element != INDEX_NONE)
			{
				_handlers->Events.RemoveAt(element);
			}
		}
	}
}

void UU5_EventSystem_ACC::SetEventValueS(const FString& _eventTag, float _value)
{
	mU5_FUNCMESS(true, _eventTag);
	FEventHandlers* handleStruct = EventSystemData.Events.Find(_eventTag);
	if (!handleStruct)
	{
		handleStruct = &EventSystemData.Events.Add(_eventTag, FEventHandlers());
	}
	handleStruct->Value = _value;
	for (UU5_Event_ACC* event : handleStruct->Events)
	{
		event->SetEventValue(_eventTag, _value);
	}
}

void UU5_EventSystem_ACC::SetEventValueH(const FDataTableRowHandle& _handle, float _value)
{
	FString eventTag; EventHandleToString(eventTag, _handle);
	SetEventValueS(eventTag, _value);
}

float UU5_EventSystem_ACC::GetEventValueS(const FString& _name)
{
	mU5_FUNCMESS(true, _name);
	if (const FEventHandlers* handlers = EventSystemData.GetEventHandlers(_name))
	{
		return handlers->Value;
	}
	return 0.f;
}

float UU5_EventSystem_ACC::GetEventValueH(const FDataTableRowHandle& _handle)
{
	FString eventTag; EventHandleToString(eventTag, _handle);
	return GetEventValueS(eventTag);
}

void UU5_EventSystem_ACC::FEventSystemData::AddEvent(const UU5_Event_ACC* _event)
{
	mU5_FUNCTION(false);
	UU5_Event_ACC* event = const_cast<UU5_Event_ACC*>(_event);
	const UU5_Event_ACC::event_data_t eventData = _event->GetEventData();
	for(const FDataTableRowHandle& element : eventData)
	{
		FString eventTag; EventHandleToString(eventTag, element);
		FEventHandlers* handleStruct = Events.Find(eventTag);
		if(!handleStruct)
		{
			handleStruct = &Events.Add(eventTag, FEventHandlers());
			if(IsSavesLoaded) NewEventDelegate->Broadcast(eventTag, event);
		}
		handleStruct->Events.AddUnique(event);
		if(IsSavesLoaded) event->SetEventValue(eventTag, handleStruct->Value);

		mU5_FUNCMESS(true, event->GetReadableName() + " bind " + eventTag);
	};
}

void UU5_EventSystem_ACC::FEventSystemData::RemoveEvent(const UU5_Event_ACC* _event)
{

}

FEventHandlers* UU5_EventSystem_ACC::FEventSystemData::GetEventHandlers(const FString& _key)
{
	return Events.Find(_key);
}

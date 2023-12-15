// Fill out your copyright notice in the Description page of Project Settings.
#include "U5_EventSystem_ACC.h"
#include "U5_Event_ACC.h"

void UU5_EventSystem_ACC::BeginPlay()
{
	Super::BeginPlay();
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

void UU5_EventSystem_ACC::CheckParent()
{
}

void UU5_EventSystem_ACC::EventHandleToString(FString& _result, const FDataTableRowHandle& _handle)
{
	_result = (_handle.DataTable.GetName() + " : " + _handle.RowName.ToString());
}

void UU5_EventSystem_ACC::RegisterEvent(UU5_Event_ACC* _event)
{
	check(_event);
	EventSystemData.AddEvent(_event);
}

void UU5_EventSystem_ACC::UnRegisterEvent(UU5_Event_ACC* _event)
{
	check(_event);
	for (FDataTableRowHandle& _handle : _event->ResponceList)
	{
		FString eventTag; EventHandleToString(eventTag, _handle);
		FEventHandlers* _handlers =  EventSystemData.GetEvents().Find(eventTag);
		if (_handlers)
		{
			int32 element = _handlers->Events.Find(_event);
			if(element != INDEX_NONE)
			{
				_handlers->Events.RemoveAt(element);
			}
		}
	}
}

void UU5_EventSystem_ACC::SetEventValueS(const FString& _eventTag, float _value)
{
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

void UU5_EventSystem_ACC::FEventSystemData::AddEvent(UU5_Event_ACC* _event)
{
	const UU5_Event_ACC::event_data_t eventData = _event->GetEventData();
	for(const FDataTableRowHandle& element : eventData)
	{
		FString eventTag; EventHandleToString(eventTag, element);
		FEventHandlers* handleStruct = Events.Find(eventTag);
		if(!handleStruct)
		{
			handleStruct = &Events.Add(eventTag, FEventHandlers());
			NewEventDelegate->Broadcast(eventTag, _event);
		}
		handleStruct->Events.AddUnique(_event);
		_event->SetEventValue(eventTag, handleStruct->Value);
	};
}

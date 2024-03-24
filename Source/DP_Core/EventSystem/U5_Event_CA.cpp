// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_Event_CA.h"


AU5_Event_CA::AU5_Event_CA()
{
	PrimaryActorTick.bCanEverTick = false;

	EventComponent = CreateDefaultSubobject<UU5_Event_ACC>(L"U5_Event_Component");
}

void AU5_Event_CA::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EventComponent->OnEventChanged_Delegate.AddDynamic(this, &ThisClass::FireEvent);
}

void AU5_Event_CA::FireEvent(const FString& _eventName, float _eventValue, UU5_Event_ACC* _event)
{
	OnEventFiredEvent.Broadcast(_eventName, _eventValue);
}


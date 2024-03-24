// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_Event_ACC.h"
#include "GameFramework/Actor.h"
#include "U5_Event_CA.generated.h"

UCLASS(Blueprintable)
class DP_CORE_API AU5_Event_CA : public AActor
{
	GENERATED_BODY()
	DECLARE_EVENT_TwoParams(AU5_Event_CA, FOnEventFired, const FString&, float);
public:
	AU5_Event_CA();
	virtual void PostInitializeComponents() override;
	FOnEventFired& OnEventFired() { return OnEventFiredEvent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UU5_Event_ACC> EventComponent;

private:
	FOnEventFired OnEventFiredEvent;

	void FireEvent(const FString& _eventName, float _eventValue, UU5_Event_ACC* _event);
};

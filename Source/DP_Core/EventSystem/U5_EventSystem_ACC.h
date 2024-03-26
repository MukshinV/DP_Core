// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "Engine/DataTable.h"

#include "U5_EventSystem_ACC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewEventRegistredDelegate, FString, EventTag, UU5_Event_ACC*, Event);

USTRUCT()
struct FEventHandlers
{
	GENERATED_BODY()

	UPROPERTY()
	float Value {0.f};

	UPROPERTY()
	TArray<UU5_Event_ACC*> Events;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DP_CORE_API UU5_EventSystem_ACC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UU5_EventSystem_ACC()
	{
		PrimaryComponentTick.bCanEverTick = false;
		EventSystemData.IsSavesLoaded = 0x0;
	}

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnComponentCreated() override;

public: // Event system.
	// Event system contains: 
	// * FEventSystemData + FEventHandlers
	// * FEventSystemData->TMap<FString, FEventHandlers> Events; - the pair <EventKey(FString, FEventHandlers)>
	// * FEventHandlers - is array of this evet key abonents, that handle any this event value change.
	UPROPERTY(BlueprintAssignable, DisplayName = "cbNewEvent")
	FNewEventRegistredDelegate OnNewEventRegistred;

	struct FEventSystemData
	{
	public: // Event handlers.
		TMap<FString, FEventHandlers> Events;

		void AddEvent(const UU5_Event_ACC* _event);
		void RemoveEvent(const UU5_Event_ACC* _event);

		void SetEventsValue() {}
		TArray<UU5_Event_ACC*>* TryGetEventsArray() {}
		TMap<FString, FEventHandlers>& GetEvents() { return Events; }

		FNewEventRegistredDelegate* NewEventDelegate = nullptr;

		FEventHandlers* GetEventHandlers(const FString& _key);
		uint8 IsSavesLoaded : 1;
	}EventSystemData;
	
	UFUNCTION(BlueprintCallable, DisplayName="!RegisterEvent(C)")
	void RegisterEvent(const UU5_Event_ACC* _event);

	UFUNCTION(BlueprintCallable, DisplayName = "!UnRegisterEvent(C)")
	void UnRegisterEvent(const UU5_Event_ACC* _event);

	UFUNCTION(BlueprintCallable, DisplayName = "!SetEventValue(C, String)")
	void SetEventValueS(const FString& _name, float _value);

	UFUNCTION(BlueprintCallable, DisplayName = "!SetEventValue(C, Handle)")
	void SetEventValueH(const FDataTableRowHandle& _name, float _value);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetEventValue(C, String)")
	float GetEventValueS(const FString& _name);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetEventValue(C, Handle)")
	float GetEventValueH(const FDataTableRowHandle& _name);

private: // Internal staff.
	void CheckParent_Internal();
};

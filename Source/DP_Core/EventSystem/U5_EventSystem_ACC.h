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
	// Sets default values for this component's properties
	UU5_EventSystem_ACC()
	{
		PrimaryComponentTick.bCanEverTick = false;
	}

protected:
	virtual void BeginPlay() override;
	virtual void OnComponentCreated() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void CheckParent();

	//! Only a true way to convert handle to string for all project.
	UFUNCTION()
	static void EventHandleToString(FString& _result, const FDataTableRowHandle& _handle);

public:
	UPROPERTY(BlueprintAssignable, DisplayName = "cbNewEvent")
	FNewEventRegistredDelegate OnNewEventRegistred;

	struct FEventSystemData
	{
		TMap<FString, FEventHandlers> Events;

		void AddEvent(UU5_Event_ACC* _event);
		void RemoveEvent(const UU5_Event_ACC* _event);

		void SetEventsValue() {}
		TArray<UU5_Event_ACC*>* TryGetEventsArray() {}
		TMap<FString, FEventHandlers>& GetEvents() { return Events; }

		FNewEventRegistredDelegate* NewEventDelegate = nullptr;
	}EventSystemData;
	
	UFUNCTION(BlueprintCallable, DisplayName="!RegisterEbvent()")
	void RegisterEvent(UU5_Event_ACC* _event);

	UFUNCTION(BlueprintCallable, DisplayName = "!UnRegisterEbvent()")
	void UnRegisterEvent(UU5_Event_ACC* _event);

	UFUNCTION(BlueprintCallable, DisplayName = "!SetEventValue(String)")
	void SetEventValueS(const FString& _name, float _value);

	UFUNCTION(BlueprintCallable, DisplayName = "!SetEventValue(Handle)")
	void SetEventValueH(const FDataTableRowHandle& _name, float _value);

};

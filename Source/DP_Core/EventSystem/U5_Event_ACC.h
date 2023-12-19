// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "U5_EventSystem_ACC.h"

#include "U5_Event_ACC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEventChangeDelegate, FString, EventName, float, EventValue, UU5_Event_ACC*, Event);

//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS(Blueprintable)
class DP_CORE_API UU5_Event_ACC : public UActorComponent
{
	GENERATED_BODY()
public:
	using event_data_t = TArray<FDataTableRowHandle>;

#pragma region Default
public:	
	// Sets default values for this component's properties
	UU5_Event_ACC()
	{
		PrimaryComponentTick.bCanEverTick = false;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void EndPlay(const EEndPlayReason::Type _reason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion Default
#pragma region Utility
	// Light internal utility fuction.
	UU5_EventSystem_ACC* TryGetEventSystem();

	// Returns TArray<FDataTableRowHandle> event_data
	const event_data_t& GetEventData() const { return ResponceList; }
#pragma endregion Utility
#pragma region Event

	// Property @ResponceList, is an array for keepeng DataTableRowHandle's,
	// thats indicate what exactly event waiting this component.
	UPROPERTY(EditAnywhere, DisplayName = "@ResponceList", Category = "‼Event")
	TArray<FDataTableRowHandle> ResponceList;

	// Property - @Value. Many events represent complex behavior that is interpreted as signed float.
	UPROPERTY(EditAnywhere, DisplayName = "@Value", Category = "‼Event")
	float Value;

	UFUNCTION(DisplayName="!SetEventValue(float)")
	void SetEventValue(const FString& _event, float _value);

	UPROPERTY(BlueprintAssignable, DisplayName="cbEventChanged")
	FEventChangeDelegate OnEventChanged_Delegate;

#pragma endregion Event
};

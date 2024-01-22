#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "U5_EventSystem_ACC.h"

#include "U5_Event_ACC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEventChangeDelegate, FString, EventName, float, EventValue, UU5_Event_ACC*, Event);

UCLASS(Blueprintable)
class DP_CORE_API UU5_Event_ACC : public UActorComponent
{
	GENERATED_BODY()
public:
	using event_data_t = TArray<FDataTableRowHandle>;

#pragma region Default
public:	
	UU5_Event_ACC()
	{
		PrimaryComponentTick.bCanEverTick = false;
	}

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void EndPlay(const EEndPlayReason::Type _reason) override;

public: // Responce list.
	UPROPERTY(EditAnywhere, DisplayName = "@ResponceList", Category = "‼Event")
	TArray<FDataTableRowHandle> ResponceList;

	const event_data_t& GetEventData() const { return ResponceList; }

	// Property - @Value. Many events represent complex behavior that is interpreted as signed float.
	UPROPERTY(EditAnywhere, DisplayName = "@Value", Category = "‼Event")
	float Value;

	UFUNCTION(DisplayName="!SetEventValue(float)")
	void SetEventValue(const FString& _event, float _value);

	UPROPERTY(BlueprintAssignable, DisplayName="cbEvent")
	FEventChangeDelegate OnEventChanged_Delegate;

private: // Utility.
	UU5_EventSystem_ACC* TryGetEventSystem();
};

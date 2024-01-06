#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "U5_Behavior_ACC.generated.h"

class UU5_Controller_ACC;

UCLASS( Blueprintable )
class DP_CORE_API UU5_Behavior_ACC : public UActorComponent
{
	GENERATED_BODY()

public:
	UU5_Behavior_ACC()
	{
		PrimaryComponentTick.bCanEverTick = false;
		SetIsReplicatedByDefault(true);
	}
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
	{
		DOREPLIFETIME(UU5_Behavior_ACC, ControllerBehavior);
	}

public: // Controller Behavior

	UPROPERTY(ReplicatedUsing = Rep_ControllerBehavior, DisplayName="@ControllerBehavior")
	mutable TObjectPtr<UU5_Controller_ACC> ControllerBehavior = nullptr;

	UFUNCTION()
	void Rep_ControllerBehavior();

	UFUNCTION()
	void RegisterInController(const UU5_Controller_ACC* _controllerBehavior);

	UFUNCTION()
	void UnregisterInController(const UU5_Controller_ACC* _controllerBehavior);

public:
	UFUNCTION(BlueprintCallable)
	bool HandleInputEvent() { return false; }

};

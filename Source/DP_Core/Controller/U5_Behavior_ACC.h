#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "U5_Behavior_ACC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewController);

class UU5_Controller_ACC;

UCLASS( Blueprintable )
class DP_CORE_API UU5_Behavior_ACC : public UActorComponent
{
	GENERATED_BODY()

public:
	UU5_Behavior_ACC(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
		:Super(ObjectInitializer)
	{
		PrimaryComponentTick.bCanEverTick = true;
		SetIsReplicatedByDefault(true);
		bAutoActivate = true;
	}
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public: // Controller Behavior.

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = Rep_ControllerBehavior, DisplayName="@ControllerBehavior")
	UU5_Controller_ACC* ControllerBehavior = nullptr;

	UFUNCTION(BlueprintCallable, DisplayName="!GetControllerACC()")
	UU5_Controller_ACC* GetControllerACC();

	UPROPERTY(BlueprintAssignable)
	FNewController cbNewController;

	UFUNCTION()
	void Rep_ControllerBehavior(UU5_Controller_ACC* _OldController);

	UFUNCTION()
	void RegisterInController(const UU5_Controller_ACC* _controllerBehavior);

	UFUNCTION()
	void UnregisterInController(const UU5_Controller_ACC* _controllerBehavior);

public: // Input Events.

	UFUNCTION(BlueprintCallable)
	bool HandleInputEvent() { return false; }

};

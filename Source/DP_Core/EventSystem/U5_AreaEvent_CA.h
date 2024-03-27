// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_Event_CA.h"
#include "U5_AreaEvent_CA.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAreaActivated);

USTRUCT(BlueprintType)
struct FU5_AreaActivationEventHandle_Struct
{
	GENERATED_BODY()
public:
	FU5_AreaActivationEventHandle_Struct() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@EventHandleC")
	FDataTableRowHandle EventHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@FireValueC")
	float FireValue;
};


UCLASS(Blueprintable)
class DP_CORE_API AU5_AreaEvent_CA : public AU5_Event_CA
{
	GENERATED_BODY()

public: // Area Activation.
	AU5_AreaEvent_CA();
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!OnAreaActivatedC")
	void OnAreaActivated();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!OnAreaDeactivatedC")
	void OnAreaDeactivated();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!OnActorStartedOverlapC")
	void OnActorStartedOverlap(AActor* _otherActor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!OnActorEndedOverlapC")
	void OnActorEndedOverlap(AActor* _otherActor);

	UFUNCTION(BlueprintCallable, DisplayName="!ActivateThisArea(C, Virtual)")
	virtual void ActivateThisArea();
	UFUNCTION(BlueprintCallable, DisplayName="!ActivateFX(C, Virtual)(bool)")
	virtual void ActivateFX(bool _isActive);

	UFUNCTION(BlueprintCallable, DisplayName = "!AfterActivateArea(C, Virtual)")
	virtual void AfterAreaActivated();

public: // Dispathers.
	UPROPERTY(BlueprintAssignable)
	FAreaActivated cbAreaActivated;

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor, DisplayName="!MakeActive(OnlyEditor)")
	virtual void MakeActive();
	UFUNCTION(BlueprintCallable, CallInEditor, DisplayName="!SwitchOff(OnlyEditor)")
	virtual void SwitchOff();
	UFUNCTION(BlueprintCallable, CallInEditor, DisplayName="!ShowBounds(OnlyEditor)")
	virtual void ShowBounds();
#endif
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@AreaActivationEventsC")
	TArray<FU5_AreaActivationEventHandle_Struct> AreaActivationEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@AreaDeactivationEventsC")
	TArray<FU5_AreaActivationEventHandle_Struct> AreaDeactivationEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@IsAreaActiveC")
	bool bIsAreaActive;

	UFUNCTION(BlueprintCallable, DisplayName="!IsLocalPlayer(Actor)")
	bool IsLocalPlayer(AActor* _actor) const;
};

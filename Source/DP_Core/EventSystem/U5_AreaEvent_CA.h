// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_Event_CA.h"
#include "U5_AreaEvent_CA.generated.h"

USTRUCT(BlueprintType)
struct FAreaActivationEventHandle
{
	GENERATED_BODY()
public:
	FAreaActivationEventHandle() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@EventHandleC")
	FDataTableRowHandle EventHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@FireValueC")
	float FireValue;
};


UCLASS(Blueprintable)
class DP_CORE_API AU5_AreaEvent_CA : public AU5_Event_CA
{
	GENERATED_BODY()

public:
	AU5_AreaEvent_CA();
	
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
	TArray<FAreaActivationEventHandle> AreaActivationEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@AreaDeactivationEventsC")
	TArray<FAreaActivationEventHandle> AreaDeactivationEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@IsAreaActiveC")
	bool bIsAreaActive;

	UFUNCTION(BlueprintCallable, DisplayName="!IsLocalPlayer(Actor)")
	bool IsLocalPlayer(AActor* _actor) const;
};

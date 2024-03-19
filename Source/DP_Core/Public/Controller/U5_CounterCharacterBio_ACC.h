// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/U5_CharacterBio_ACC.h"
#include "U5_CounterCharacterBio_ACC.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthBarChangedDelegate, int32, HealthBarCount);


UCLASS()
class DP_CORE_API UU5_CounterCharacterBio_ACC : public UU5_CharacterBio_ACC
{
	GENERATED_BODY()
	
public: // Attribute Health
	virtual void OnDeathBecame() override;

	UFUNCTION(BlueprintPure, DisplayName = "!HasHealthBars(C)")
	FORCEINLINE bool HasHealthBars() const { return HealthBarCount < HealthBarSize; }

	UFUNCTION(BlueprintPure, DisplayName = "!GetHealthBarCount(C)")
	FORCEINLINE int32 GetHealthBarCount() const { return HealthBarCount; }

protected:
	UFUNCTION(BlueprintCallable, DisplayName = "!UpdateHealthBar(C)")
	void UpdateHealthBar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "@HealthBarCount")
	int32 HealthBarSize{ 1 };

	int32 HealthBarCount{ 1 };


public: // Delegates
	UPROPERTY(BlueprintAssignable)
	FOnHealthBarChangedDelegate cbHealthBarChangedDelegate;
};

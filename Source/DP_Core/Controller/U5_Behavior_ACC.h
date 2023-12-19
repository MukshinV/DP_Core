// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "U5_Behavior_ACC.generated.h"


UCLASS( Blueprintable )
class DP_CORE_API UU5_Behavior_ACC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UU5_Behavior_ACC() 
	{ 
		PrimaryComponentTick.bCanEverTick = false;
	}
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool HandleInputEvent() { return false; }


};

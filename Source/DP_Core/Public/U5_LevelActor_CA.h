// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_Level_CA.h"
#include "GameFramework/Actor.h"
#include "U5_LevelActor_CA.generated.h"

UCLASS()
class DP_CORE_API AU5_LevelActor_CA : public AU5_Level_CA
{
	GENERATED_BODY()

public:
	AU5_LevelActor_CA();
	virtual void StartGame_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@EventsC")
	TArray<FDataTableRowHandle> Events;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@DefaultLevelEventsC")
	TArray<UDataTable*> DefaultLevelEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@LoadStateEventHandleC")
	FDataTableRowHandle LoadStateEventHandle;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!RunDefaultEventValues(C, Virtual)")
	void RunDefaultEventValues();
};

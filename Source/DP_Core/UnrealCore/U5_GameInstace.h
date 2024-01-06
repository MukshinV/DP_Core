// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Components/ActorComponent.h"
#include "U5_GameInstace.generated.h"

class APlayerController;
class UU5_Controller_ACC;
UCLASS(Blueprintable)
class DP_CORE_API UU5_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, DisplayName="@LocalController")
	TObjectPtr<APlayerController> Controller = nullptr;

	UFUNCTION(DisplayName = "!SetLocalController()")
	void SetLocalController(APlayerController* _controller);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetLocalController()")
	APlayerController* GetLocalController(bool _native);

public:
	UPROPERTY(BlueprintReadOnly, DisplayName = "@ControllerBehavior")
	TObjectPtr<UU5_Controller_ACC> ControllerACC = nullptr;

	UFUNCTION(DisplayName="!SetControllerBehavior()")
	void SetControllerBehavior(UU5_Controller_ACC* _controllerAcc);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetLocalControllerACC()")
	UU5_Controller_ACC* GetControllerBehavior();
};

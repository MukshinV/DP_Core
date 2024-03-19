// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveSystem/U5_CheckpointSystem_CU.h"
#include "U5_GameInstace.generated.h"

UCLASS(Blueprintable)
class DP_CORE_API UU5_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
public:
	UPROPERTY(BlueprintReadOnly, DisplayName="@LocalController")
	class APlayerController* LocalController = nullptr;

	UFUNCTION(DisplayName = "!SetLocalController()")
	void SetLocalController(const APlayerController* _controller);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetLocalController()")
	APlayerController* GetLocalController(bool _native);

public:
	UPROPERTY(BlueprintReadOnly, DisplayName = "@ControllerBehavior")
	TObjectPtr<class UU5_Controller_ACC> ControllerACC = nullptr;

	UFUNCTION(DisplayName="!SetControllerBehavior()")
	void SetControllerBehavior(UU5_Controller_ACC* _controllerAcc);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetLocalControllerACC()")
	UU5_Controller_ACC* GetControllerBehavior();

public: // Level Actor.
	TObjectPtr<class AU5_Level_CA> LevelActor = nullptr;
	
	UFUNCTION(DisplayName="!RegisterLevelActor()")
	void RegisterLevelActor(const AU5_Level_CA* _level);
	
	UFUNCTION(DisplayName="!RegisterLevelActor()")
	void UnRegisterLevelActor(const AU5_Level_CA* _level);

	UFUNCTION(BlueprintCallable, DisplayName="!GetLevelActor()")
	AU5_Level_CA* GetLevelActor() const;

public: //Checkpoint system
	UFUNCTION(BlueprintCallable, DisplayName="!GetCheckpointSystem(C)")
	UU5_CheckpointSystem_CU* GetCheckpointSystem() const { return CheckpointSystem; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="@CheckpointSystemC")
	TObjectPtr<UU5_CheckpointSystem_CU> CheckpointSystem;
};

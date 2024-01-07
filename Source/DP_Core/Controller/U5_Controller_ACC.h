// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "U5_Controller_ACC.generated.h"

class UU5_GameInstance;
class UU5_Behavior_ACC;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewCurrentBahavior);

UCLASS( Blueprintable, ClassGroup=(U5), meta=(BlueprintSpawnableComponent) )
class DP_CORE_API UU5_Controller_ACC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UU5_Controller_ACC() 
	{ 
		PrimaryComponentTick.bCanEverTick = false;
	}
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:// Behavior cascade.
	
	UPROPERTY(DisplayName="@BehaviorCascade")
	TArray<UU5_Behavior_ACC*> BehaviorsCascade;

public:// Local Player Controller.

	UPROPERTY(VisibleAnywhere, DisplayName="@Controller")
	TObjectPtr<APlayerController> Controller = nullptr;

public: // Game Instance.
	TObjectPtr<UU5_GameInstance> GameInstance = nullptr;
	void OnRegisterByGameInst(const UU5_GameInstance* _gameInst);

public:// Current Behavior.

	UPROPERTY(BlueprintReadOnly, DisplayName="@CurrentBehavior")
	TObjectPtr<UU5_Behavior_ACC> CurrentBehavior = nullptr;

	UPROPERTY(BlueprintAssignable)
	FNewCurrentBahavior cbNewBehavior;

	UFUNCTION(BlueprintCallable, DisplayName="!RegisterCurrentBehavior()")
	void RegisterCurrentBehavior(UU5_Behavior_ACC* _behavior);

	UFUNCTION(DisplayName="!PossesSuccesed")
	void OnPossesSucces(const UU5_Behavior_ACC* _behavior);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "U5_Controller_ACC.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

public:
	class UU5_Behavior_ACC;
	UPROPERTY(DisplayName="@Cascade")
	TArray<UU5_Behavior_ACC*> BehaviorsCascade;

};

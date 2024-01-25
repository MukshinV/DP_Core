// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_Controller_ACC.h"
#include "Kismet/GameplayStatics.h"

#include "../UnrealCore/U5_GameInstace.h"
#include "../Controller/U5_Behavior_ACC.h"
#include "../Utils/U5_Utils.h"

void UU5_Controller_ACC::BeginPlay()
{
	Super::BeginPlay();
	InitControllerInGI_Internal();
}

void UU5_Controller_ACC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	mU5_FUNCTION(false);
	Super::EndPlay(EndPlayReason);
	if (Controller->IsLocalController())
	{
		UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(UGameplayStatics::GetGameInstance(GetOwner()));
		if (gameInstance)
		{
			gameInstance->SetLocalController(nullptr);
		}
	}
}

void UU5_Controller_ACC::PostInitProperties()
{
	Super::PostInitProperties();
}

void UU5_Controller_ACC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UU5_Controller_ACC::OnRegisterByGameInst(const UU5_GameInstance* _gameInst)
{
	GameInstance = const_cast<UU5_GameInstance*>(_gameInst);
}

void UU5_Controller_ACC::RegisterCurrentBehavior(UU5_Behavior_ACC* _behavior)
{
	if (_behavior)
	{
		_behavior->RegisterInController(this);
	}
	else
	{
		OnPossesSucces(nullptr);
	}
}

void UU5_Controller_ACC::OnPossesSucces(const UU5_Behavior_ACC* _behavior)
{
	UU5_Behavior_ACC* previous = CurrentBehavior;
	if (CurrentBehavior)
	{
		CurrentBehavior->UnregisterInController(this);
	}
	CurrentBehavior = const_cast<UU5_Behavior_ACC*>(_behavior);
	if (previous != CurrentBehavior)
	{
		cbNewBehavior.Broadcast();
	}
}

void UU5_Controller_ACC::InitControllerInGI_Internal()
{
	// Check parent is Controller.
	{
		Controller = Cast<APlayerController>(GetOwner());
		check(Controller);

	}

	// Register in game instance.
	if (Controller->IsLocalController())
	{
		UGameInstance* gi = UGameplayStatics::GetGameInstance(GetOwner());
		UU5_GameInstance* gameInst_ = Cast<UU5_GameInstance>(gi);
		if (gameInst_)
		{
			gameInst_->SetLocalController(Controller);
		}
	}
}


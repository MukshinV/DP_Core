// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_AreaEvent_CA.h"

#include "U5_Event_BlueprintLibrary.h"
#include "Components/DirectionalLightComponent.h"
#include "Controller/U5_Behavior_ACC.h"
#include "Controller/U5_Controller_ACC.h"
#include "Net/UnrealNetwork.h"
#include "UnrealCore/U5_Area_GI_CU.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Utils/U5_Utils.h"

AU5_AreaEvent_CA::AU5_AreaEvent_CA()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AU5_AreaEvent_CA::ActivateThisArea()
{
	OnAreaActivated_Implementation();
}

void AU5_AreaEvent_CA::ActivateFX(bool _isActive)
{
	TArray<UDirectionalLightComponent*> directionalLights{};
	GetComponents<UDirectionalLightComponent>(directionalLights);

	for (int32 i = 0; i < directionalLights.Num(); ++i)
	{
		directionalLights[i]->SetVisibility(_isActive);
	}

	TArray<UExponentialHeightFogComponent*> exponentialFogs{};
	GetComponents<UExponentialHeightFogComponent>(exponentialFogs);

	for (int32 i = 0; i < exponentialFogs.Num(); ++i)
	{
		exponentialFogs[i]->SetVisibility(_isActive);
	}
}

#if WITH_EDITOR

void AU5_AreaEvent_CA::MakeActive()
{
	SwitchOff();
	ActivateFX(true);
}

void AU5_AreaEvent_CA::SwitchOff()
{
	TArray<AActor*> areaEvents{};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AU5_AreaEvent_CA::StaticClass(), areaEvents);

	for(int32 i = 0; i < areaEvents.Num(); ++i)
	{
		Cast<AU5_AreaEvent_CA>(areaEvents[i])->ActivateFX(false);
	}
}

void AU5_AreaEvent_CA::ShowBounds()
{
	TArray<UActorComponent*> bounds = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName{L"!HiddenBounds()"});
	bool bIsVisible = false;
	
	for(int32 i = 0; i < bounds.Num(); ++i)
	{
		UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(bounds[i]);
		bIsVisible = staticMesh->IsVisible();
	}

	for(int32 i = 0; i < bounds.Num(); ++i)
	{
		UStaticMeshComponent* staticMesh = Cast<UStaticMeshComponent>(bounds[i]);
		staticMesh->SetVisibility(!bIsVisible);
	}
}

#endif

bool AU5_AreaEvent_CA::IsLocalPlayer(AActor* _actor) const
{
	const UU5_Behavior_ACC* foundBehaviour = _actor->FindComponentByClass<UU5_Behavior_ACC>();
	if(!foundBehaviour) return false;

	UU5_Area_GI_CU* gameInstance = Cast<UU5_Area_GI_CU>(GetGameInstance());
	if(!gameInstance) return false;

	const UU5_Controller_ACC* controller = gameInstance->GetControllerBehavior();
	if(!controller) return false;

	return controller->CurrentBehavior == foundBehaviour;
}

void AU5_AreaEvent_CA::OnActorStartedOverlap_Implementation(AActor* _otherActor)
{
	if(!IsLocalPlayer(_otherActor)) return;
	
	UU5_Area_GI_CU* gameInstance = Cast<UU5_Area_GI_CU>(GetGameInstance());
	if(!gameInstance) return;

	gameInstance->PushArea(this);

	bIsAreaActive = true;
	OnAreaActivated_Implementation();
}

void AU5_AreaEvent_CA::OnActorEndedOverlap_Implementation(AActor* _otherActor)
{
	if(!IsLocalPlayer(_otherActor)) return;

	UU5_Area_GI_CU* gameInstance = Cast<UU5_Area_GI_CU>(GetGameInstance());
	if(!gameInstance) return;

	gameInstance->RemoveArea(this);

	bIsAreaActive = false;
	OnAreaActivated_Implementation();
}

void AU5_AreaEvent_CA::OnAreaActivated_Implementation()
{
	const UWorld* world = GetWorld();
	FString eventString{};

	for (int32 i = 0; i < AreaActivationEvents.Num(); ++i)
	{
		FAreaActivationEventHandle& currentHandle = AreaActivationEvents[i];
		UU5_Event_BlueprintLibrary::EventHandleToString(eventString, currentHandle.EventHandle);
		UU5_Event_BlueprintLibrary::SetEventValue(world, eventString, currentHandle.FireValue);
	}

	mU5_DEBUGOUT(true, L"Area activated: " << mDNAME(this));
}

void AU5_AreaEvent_CA::OnAreaDeactivated_Implementation()
{
	const UWorld* world = GetWorld();
	FString eventString{};

	for (int32 i = 0; i < AreaDeactivationEvents.Num(); ++i)
	{
		FAreaActivationEventHandle& currentHandle = AreaActivationEvents[i];
		UU5_Event_BlueprintLibrary::EventHandleToString(eventString, currentHandle.EventHandle);
		UU5_Event_BlueprintLibrary::SetEventValue(world, eventString, currentHandle.FireValue);
	}

	mU5_DEBUGOUT(true, L"Area deactivated: " << mDNAME(this));
}



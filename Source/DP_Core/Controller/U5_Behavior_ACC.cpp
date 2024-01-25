#include "U5_Behavior_ACC.h"
#include "../Controller/U5_Controller_ACC.h"
#include "../Utils/U5_Utils.h"

void UU5_Behavior_ACC::BeginPlay()
{
	Super::BeginPlay();
}

void UU5_Behavior_ACC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ControllerBehavior, COND_None, REPNOTIFY_Always);
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UU5_Behavior_ACC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ControllerBehavior)
	{
		ControllerBehavior->RegisterCurrentBehavior(nullptr);
	}
}

void UU5_Behavior_ACC::PostInitProperties()
{
	Super::PostInitProperties();
}

UU5_Controller_ACC* UU5_Behavior_ACC::GetControllerACC()
{
	return ControllerBehavior;
}

void UU5_Behavior_ACC::Rep_ControllerBehavior(UU5_Controller_ACC* _OldController)
{
	mU5_DEBUGOUT(true, TEXT("Replication Success"));
	ControllerBehavior->OnPossesSucces(this);
}

// @param _controllerBehavior can be NULL.
void UU5_Behavior_ACC::RegisterInController(const UU5_Controller_ACC* _controllerBehavior)
{
	ControllerBehavior = const_cast<UU5_Controller_ACC*>(_controllerBehavior);
	if (true && GetOwner()->GetRemoteRole() == ENetRole::ROLE_SimulatedProxy)
	{
		Rep_ControllerBehavior(ControllerBehavior);
	}
}

void UU5_Behavior_ACC::UnregisterInController(const UU5_Controller_ACC* _controllerBehavior)
{
	ControllerBehavior = nullptr;
}

void UU5_Behavior_ACC::InitBehaviorInGI_Internal()
{

}


// Called every frame
void UU5_Behavior_ACC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

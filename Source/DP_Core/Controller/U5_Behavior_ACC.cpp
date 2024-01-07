#include "U5_Behavior_ACC.h"
#include "../Controller/U5_Controller_ACC.h"
#include "../Utils/U5_Utils.h"

void UU5_Behavior_ACC::BeginPlay()
{
	Super::BeginPlay();
}

void UU5_Behavior_ACC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}

UU5_Controller_ACC* UU5_Behavior_ACC::GetControllerACC()
{
	return ControllerBehavior;
}

void UU5_Behavior_ACC::Rep_ControllerBehavior()
{
	ControllerBehavior->OnPossesSucces(this);
}

// @param _controllerBehavior can be NULL.
void UU5_Behavior_ACC::RegisterInController(const UU5_Controller_ACC* _controllerBehavior)
{
	ControllerBehavior = const_cast<UU5_Controller_ACC*>(_controllerBehavior);
}

void UU5_Behavior_ACC::UnregisterInController(const UU5_Controller_ACC* _controllerBehavior)
{
	ControllerBehavior = nullptr;
}


// Called every frame
void UU5_Behavior_ACC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

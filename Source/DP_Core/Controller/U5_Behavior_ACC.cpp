#include "U5_Behavior_ACC.h"

void UU5_Behavior_ACC::BeginPlay()
{
	Super::BeginPlay();
}

void UU5_Behavior_ACC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}

void UU5_Behavior_ACC::Rep_ControllerBehavior()
{
	ControllerBehavior->OnPossesSucces(this);
}

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

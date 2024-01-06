#include "U5_GameInstace.h"
#include "../Controller/U5_Controller_ACC.h"

void UU5_GameInstance::SetLocalController(APlayerController* _controller)
{
    check(_controller);
    Controller = _controller;

    if (UU5_Controller_ACC* controllerBehavior = Controller->FindComponentByClass<UU5_Controller_ACC>())
    {
        controllerBehavior->OnRegisterByGameInst(this);
    }
}

APlayerController* UU5_GameInstance::GetLocalController(bool _native)
{
    return nullptr;
}

void UU5_GameInstance::SetControllerBehavior(UU5_Controller_ACC* _controllerAcc)
{
    ControllerACC = _controllerAcc;
}

UU5_Controller_ACC* UU5_GameInstance::GetControllerBehavior()
{
    return ControllerACC;
}

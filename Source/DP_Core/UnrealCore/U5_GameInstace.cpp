#include "U5_GameInstace.h"
#include "../Controller/U5_Controller_ACC.h"
#include "../Utils/U5_Utils.h"

void UU5_GameInstance::SetLocalController(const APlayerController* _controller)
{
    LocalController = const_cast<APlayerController*>(_controller);
    if (LocalController)
    {
        if (UU5_Controller_ACC* controllerBehavior = LocalController->FindComponentByClass<UU5_Controller_ACC>())
        {
            SetControllerBehavior(controllerBehavior);
        }
    }
    
}

APlayerController* UU5_GameInstance::GetLocalController(bool _native)
{
    if (_native)
    {
        return GetPrimaryPlayerController();
    }
    return LocalController;
}

void UU5_GameInstance::SetControllerBehavior(UU5_Controller_ACC* _controllerAcc)
{
    ControllerACC = _controllerAcc;
    if (ControllerACC)
    {
        ControllerACC->OnRegisterByGameInst(this);
    }
}

UU5_Controller_ACC* UU5_GameInstance::GetControllerBehavior()
{
    return ControllerACC;
}

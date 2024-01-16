#include "U5_GameInstace.h"
#include "../Controller/U5_Controller_ACC.h"
#include "../Utils/U5_Utils.h"
#include "U5_Level_CA.h"

void UU5_GameInstance::SetLocalController(const APlayerController* _controller)
{
    mU5_FUNCTION(true,"");
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
    mU5_FUNCTION(true, "");
    ControllerACC = _controllerAcc;
    if (ControllerACC)
    {
        ControllerACC->OnRegisterByGameInst(this);
    }
}

UU5_Controller_ACC* UU5_GameInstance::GetControllerBehavior()
{
    mU5_FUNCTION(true, "");
    return ControllerACC;
}

void UU5_GameInstance::RegisterLevelActor(const AU5_Level_CA* _level)
{
    // Only one LevelActor can be at level.
    check(!LevelActor);
    LevelActor = const_cast<AU5_Level_CA*>(_level);
    check(LevelActor);
}

void UU5_GameInstance::UnRegisterLevelActor(const AU5_Level_CA* _level)
{
    check(LevelActor);
    if (LevelActor == _level)
    {
        LevelActor = nullptr;
    }
}

AU5_Level_CA* UU5_GameInstance::GetLevelActor() const
{
    return LevelActor;
}

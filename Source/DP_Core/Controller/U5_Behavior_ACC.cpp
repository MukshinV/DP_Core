#include "U5_Behavior_ACC.h"
#include "../Controller/U5_Controller_ACC.h"
#include "../Utils/U5_Utils.h"
#include "Kismet/KismetMathLibrary.h"

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

void UU5_Behavior_ACC::UpdateRotationsCamera()
{
	const float newCameraDelta = FMath::Abs(FMath::Abs(FrameControlRotation.Yaw) - FMath::Abs(FrameBodyRotation.Yaw));
	float cameraYawFactor = 1.0f;
	
	if(newCameraDelta > PreviousYawCameraDelta)
	{
		const float clampedDistanceFactor = FMath::GetMappedRangeValueClamped<float, float>({0.0f, HorizontalCameraYawConstrainValue}, {0.01f, 0.99f}, newCameraDelta);
		cameraYawFactor = CameraYawConstrainCurve->GetFloatValue(clampedDistanceFactor);
	}

	PreviousControlRotation = FrameControlRotation;

	const float newPitch = FrameCameraDelta.Y + FrameControlRotation.Pitch;
	const float newYaw = FrameCameraDelta.X * cameraYawFactor + FrameControlRotation.Yaw;

	FrameControlRotation.Pitch = FMath::Clamp(newPitch, -85.0f, 85.0f);
	FrameControlRotation.Yaw = newYaw;

	PreviousYawCameraDelta = newCameraDelta;

	ClampCameraYawByBodyRotation();
}

void UU5_Behavior_ACC::ClampCameraYawByBodyRotation()
{
	const float rightConstrain = FrameBodyRotation.Yaw + HorizontalCameraYawConstrainValue;
	const float leftConstrain = FrameBodyRotation.Yaw - HorizontalCameraYawConstrainValue;
	
	FrameControlRotation.Yaw = FMath::Clamp(FrameControlRotation.Yaw, leftConstrain, rightConstrain); 
}

void UU5_Behavior_ACC::ApplyRotations()
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());

	if(!PawnOwner) return;
	if(!PawnOwner->Controller) return;

	PawnOwner->Controller->SetControlRotation(FrameControlRotation);
	PawnOwner->SetActorRotation(FrameBodyRotation);
	FrameCameraDelta = {0.0f, 0.0f};
}


// Called every frame
void UU5_Behavior_ACC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

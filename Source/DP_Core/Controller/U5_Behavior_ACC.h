#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"

#include "../EventSystem/U5_Event_ACC.h"

#include "U5_Behavior_ACC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewController);

class UU5_Controller_ACC;

UCLASS( Blueprintable )
class DP_CORE_API UU5_Behavior_ACC : public UU5_Event_ACC
{
	GENERATED_BODY()

public:
	UU5_Behavior_ACC(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
		:Super(ObjectInitializer)
	{
		PrimaryComponentTick.bCanEverTick = true;
		SetIsReplicatedByDefault(true);
		bAutoActivate = true;
	}
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitProperties() override;

public: // Controller Behavior.

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = Rep_ControllerBehavior, DisplayName="@ControllerBehavior")
	UU5_Controller_ACC* ControllerBehavior = nullptr;

	UFUNCTION(BlueprintCallable, DisplayName="!GetControllerACC()")
	UU5_Controller_ACC* GetControllerACC();

	UPROPERTY(BlueprintAssignable)
	FNewController cbNewController;

	UFUNCTION()
	void Rep_ControllerBehavior(UU5_Controller_ACC* _OldController);

	UFUNCTION()
	void RegisterInController(const UU5_Controller_ACC* _controllerBehavior);

	UFUNCTION()
	void UnregisterInController(const UU5_Controller_ACC* _controllerBehavior);

public: // Input Events.

	UFUNCTION(BlueprintCallable)
	bool HandleInputEvent() { return false; }

public: // Gameplay reports.

	UFUNCTION(BlueprintImplementableEvent, DisplayName="Report_OnThisBehaviorspawnIsDead(Virtual)", Category = "Reports")
	void Report_OnThisBehaviorspawnIsDead();

private: // Internal staff.
	void InitBehaviorInGI_Internal();

public: // Transform calcultations
	UFUNCTION(BlueprintCallable, DisplayName = "!SetAutoBodyRotationEnabled(C)", Category = "Rotation")
	void SetAutoBodyRotationEnabled(bool Enable) { EnableAutoBodyRotation = Enable; }

	UFUNCTION(BlueprintPure, DisplayName = "!IsAutoBodyRotationEnabled(C)", Category = "Rotation")
	FORCEINLINE bool IsAutoBodyRotationEnabled() const { return EnableAutoBodyRotation; };

	UFUNCTION(BlueprintPure, DisplayName = "!IsAutoBodyRotationEnabled(C)", Category = "Rotation")
	FRotator GetFrameBodyRotation() const;

public: //FX
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="!SetCurrentParticles(C, Virtual)(NiagaraComponent)")
	void SetCurrentParticles(UNiagaraComponent* _particles);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName="@CameraYawConstrainCurveC")
	TObjectPtr<class UCurveFloat> CameraYawConstrainCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@HorizontalCameraYawConstrainValueC")
	FVector2D HorizontalCameraYawConstrainValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@PreviousControlRotationC")
	FRotator PreviousControlRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@FrameControlRotationC")
	FRotator FrameControlRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@FrameBodyRotationC")
	FRotator FrameBodyRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@RotationTimeC")
	float RotationTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@PreviousYawCameraDeltaC")
	float PreviousYawCameraDelta;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@FrameCameraDeltaC")
	FVector2D FrameCameraDelta;

	FRotator InterpFrameBodyRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "@FrameBodyRotationInterpSpeed")
	float FrameBodyRotationInterpSpeed{ 5.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "@FrameCameraDeltaC")
	bool EnableAutoBodyRotation{ true };

	UFUNCTION(BlueprintCallable, DisplayName="!UpdateRotationsCamera(C)")
	virtual void UpdateRotationsCamera();
	UFUNCTION(BlueprintCallable, DisplayName="!ClampCameraYawByBodyRotation(C)")
	virtual void ClampCameraYawByBodyRotation();
	UFUNCTION(BlueprintCallable, DisplayName="!ApplyRotations(C)")
	virtual void ApplyRotations();
};

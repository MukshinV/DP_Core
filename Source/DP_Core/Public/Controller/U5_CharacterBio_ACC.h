
#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GenericTeamAgentInterface.h"

#include "Data/U5_CharacterBio_Data.h"

#include "U5_CharacterBio_ACC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

class UU5_CharacterBio_ACC;

class Attribute_Health
{
public:
	Attribute_Health() : This(nullptr) {}
	Attribute_Health(UU5_CharacterBio_ACC* _this) { This = _this; }

public: // Health
	float Health = 100;
	FVector2D Limit { 0, 100 };

	void Modify(bool _positive, float _value);
	float Reset();
	float Get() const;

private:
	UPROPERTY()
	UU5_CharacterBio_ACC* This;
	
	void Check_Internal();
	UU5_CharacterBio_ACC* GetOwner() const { return This; }
};

class Attribute_Stamina
{
public:
	Attribute_Stamina() : Attribute_Stamina(nullptr) {}
	Attribute_Stamina(UU5_CharacterBio_ACC* _this)
	{
		This = _this;

		Stamina = CapacityLimit.Y;
		Capacity = CapacityLimit.Y;
	}

public:
	float Stamina = 100;
	float Capacity = 100; 
	FVector2D CapacityLimit { 30, 100 };

	void ModifyStaminaValue(bool _positive, float _value);
	void ModifyStaminaCapacity(bool _positive, float _value);
	float GetStaminaValue() const;
	float GetStaminaCapacity() const;
	float GetNormalizedStaminaValue() const;
	float GetNormalizedStaminaCapacity() const;

private:
	UPROPERTY()
	UU5_CharacterBio_ACC* This;
	
	UU5_CharacterBio_ACC* GetOwner() const { return This; }

	void UpdateStaminaValue();
	void UpdateStaminaCapacity();
};

class Attribute_Battery
{
public:
	Attribute_Battery() : This(nullptr) {}
	Attribute_Battery(UU5_CharacterBio_ACC* _this) { This = _this; }

public:
	float Battery = 100;
	FVector2D Limit { 0, 100 };
	
	void Modify(bool _positive, float _value);
	float Get() const;

private:
	UPROPERTY()
	UU5_CharacterBio_ACC* This;
	
	UU5_CharacterBio_ACC* GetOwner() const { return This; }
	void Check_Internal(float _incomingValue);
};

UCLASS(Blueprintable)
class DP_CORE_API UU5_CharacterBio_ACC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UU5_CharacterBio_ACC() :
		Health(this),
		Stamina(this),
		Battery(this)
	{
		PrimaryComponentTick.bCanEverTick = true;
		SetComponentTickEnabled(true);
		PrimaryComponentTick.TickInterval = 0.1f;
	}

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public: // Death
	UFUNCTION(BlueprintPure, DisplayName = "!IsDead()", Category = "Death")
	FORCEINLINE bool IsDead() const { return bDead; }

protected:
	bool bDead{ false };


public: // Attribute Health

	Attribute_Health Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@HealthDamageFromFreezingPercent")
	float HealthDamageFromFreezingPercent = 0.05f;

	UFUNCTION(BlueprintCallable, DisplayName="!HealthModify(C, Virtual)")
	virtual float HealthModify(bool _positive, float _value);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetHealth(C, Virtual)")
	virtual float GetHealth() const { return Health.Get(); }

	UFUNCTION(BlueprintNativeEvent, DisplayName="!OnHealthChanged(Virtual)")
	void OnHealthChanged(float Value, float NormalizedValue);

	virtual void OnDeathBecame();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FDeathDelegate cbDeath;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="!OnDeath(Virtual)")
	void OnDeath();


public: // Attribute Stamina

	Attribute_Stamina Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@StaminaDamageFromFreezingNormalized")
	float StaminaDamageFromFreezingNormalized = 0.015f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@StaminaRestoreNormalized")
	float StaminaRestorePerSecondNormalized = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "@StaminaRestoreCooldown")
	float StaminaRestoreCooldown = 2.f;

	UFUNCTION(BlueprintCallable, DisplayName="!StaminaModify(C, Virtual)")
	virtual float StaminaModify(bool _positive, float _value);

	UFUNCTION(BlueprintCallable, DisplayName="!StaminaCapacityModify(C, Virtual)")
	virtual float StaminaCapacityModify(bool _positive, float _value);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetStaminaValue(C, Virtual)")
	virtual float GetStamina() const { return Stamina.GetStaminaValue(); }

	UFUNCTION(BlueprintCallable, DisplayName = "!GetStaminaCapacity(C, Virtual)")
	virtual float GetStaminaCapacity() const { return Stamina.GetStaminaCapacity(); }

	UFUNCTION(BlueprintCallable, DisplayName = "!GetStaminaLimits(C)")
	FVector2D GetStaminaLimits() const { return Stamina.CapacityLimit; }

	UFUNCTION(BlueprintNativeEvent, DisplayName="!OnStaminaChanged(Virtual)")
	void OnStaminaChanged(float Value, float NormalizedValue);

	UFUNCTION(BlueprintNativeEvent, DisplayName="!OnStaminaCapacityChanged(Virtual)")
	void OnStaminaCapacityChanged(float _value, float _normalizedValue);

	UFUNCTION(BlueprintCallable, DisplayName = "!EnableStaminaRestore(C)")
	void EnableStaminaRestore(bool Enable = true);

protected:
	UFUNCTION(BlueprintCallable, DisplayName = "!SetStaminaRestoreState(C)")
	virtual void SetStaminaRestoreState(EU5_Attribute_RestoreState _state);

	UFUNCTION(BlueprintCallable, DisplayName = "!StaminaRestoreTick(C)")
	virtual void StaminaRestoreTick(float DeltaTime);

	UFUNCTION(BlueprintCallable, DisplayName = "!OnStaminaRestoreStateChanged(C)")
	virtual void OnStaminaRestoreStateChanged(EU5_Attribute_RestoreState PrevState);

	UFUNCTION()
	virtual void OnStaminaCooldownEnded();

	EU5_Attribute_RestoreState StaminaRestoreState{ EU5_Attribute_RestoreState::None };

	FTimerHandle StaminaRestoreCooldownTimerHandle;


public: // Attribute Battery

	Attribute_Battery Battery;

	UFUNCTION(BlueprintCallable, DisplayName="!BatteryModify(C, Virtual)")
	virtual float BatteryModify(bool _positive, float _value);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetBattery(C, Virtual)")
	virtual float GetBattery() const { return Battery.Get(); }

	UFUNCTION(BlueprintCallable, DisplayName = "!GetBatteryLimits(C)")
	FVector2D GetBatteryLimits() const { return Battery.Limit; }

	UFUNCTION(BlueprintNativeEvent, DisplayName="!OnBatteryChanged(Virtual)")
	void OnBatteryChanged(float _value, float _normalizedValue, float _incomingValue);

public: // Attribute Sanity

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@Sanity"))
	float Sanity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@SanityLimits"))
	FVector2D SanityLimits;

public: // Team

	UFUNCTION(BlueprintCallable, Category = "Team", DisplayName = "!SetGenericTeamId()")
	void SetGenericTeamId(const FGenericTeamId& _teamId);

	UFUNCTION(BlueprintPure, Category = "Team", DisplayName = "!GetGenericTeamId()")
	FORCEINLINE FGenericTeamId GetGenericTeamId() const { return TeamId; }

	UFUNCTION(BlueprintPure, Category = "Team", DisplayName = "!GetTeamAttitudeTowards()")
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor* _other) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team", DisplayName = "@TeamId")
	FGenericTeamId TeamId;
};

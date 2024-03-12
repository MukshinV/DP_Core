#include "Controller/U5_CharacterBio_ACC.h"
#include "../Utils/U5_Utils.h"
#include "../Controller/U5_Behavior_ACC.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"


void UU5_CharacterBio_ACC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	StaminaRestoreTick(DeltaTime);
}

float UU5_CharacterBio_ACC::HealthModify(bool _positive, float _value)
{
	Health.Modify(_positive, _value);
	return Health.Health;
}

void UU5_CharacterBio_ACC::OnHealthChanged_Implementation(float Value, float NormalizedValue)
{
}

void UU5_CharacterBio_ACC::OnDeathBecame()
{
	bDead = true;

	cbDeath.Broadcast();
	OnDeath();

	UU5_Behavior_ACC* beh = GetOwner()->FindComponentByClass<UU5_Behavior_ACC>();
	if (beh)
	{
		beh->Report_OnThisBehaviorspawnIsDead();
	}

	SetComponentTickEnabled(false);
}

float UU5_CharacterBio_ACC::StaminaModify(bool _positive, float _value)
{
	Stamina.ModifyStaminaValue(_positive, _value);
	if (!_positive) SetStaminaRestoreState(EU5_Attribute_RestoreState::Cooldown);
	return Stamina.Stamina;
}

float UU5_CharacterBio_ACC::StaminaCapacityModify(bool _positive, float _value)
{
	Stamina.ModifyStaminaCapacity(_positive, _value);

	if(Stamina.Stamina > Stamina.Capacity)
	{
		const float difference = Stamina.Capacity - Stamina.Stamina; 
		Stamina.ModifyStaminaValue(false, difference);
	}
	
	return Stamina.Capacity;
}

void UU5_CharacterBio_ACC::OnStaminaCapacityChanged_Implementation(float _value, float _normalizedValue)
{
	const float deltaSeconds = GetWorld()->DeltaTimeSeconds;

	if(FMath::IsNearlyEqual(_value, Stamina.CapacityLimit.X, 0.001f))
	{
		const float healthDamageValue = Health.Limit.Y * HealthDamageFromFreezingPercent * deltaSeconds; 
		HealthModify(false, healthDamageValue);
	}
}

void UU5_CharacterBio_ACC::EnableStaminaRestore(bool Enable)
{
	if (Enable)
	{
		if (StaminaRestoreState == EU5_Attribute_RestoreState::None)
			SetStaminaRestoreState(EU5_Attribute_RestoreState::Cooldown);
	}
	else
	{
		SetStaminaRestoreState(EU5_Attribute_RestoreState::None);
	}
}

void UU5_CharacterBio_ACC::SetStaminaRestoreState(EU5_Attribute_RestoreState _state)
{
	if (_state == StaminaRestoreState) return;

	EU5_Attribute_RestoreState prev = StaminaRestoreState;
	StaminaRestoreState = _state;

	OnStaminaRestoreStateChanged(prev);
}

void UU5_CharacterBio_ACC::OnStaminaCooldownEnded()
{
	SetStaminaRestoreState(EU5_Attribute_RestoreState::Restore);
}

void UU5_CharacterBio_ACC::StaminaRestoreTick(float DeltaTime)
{
	if (StaminaRestoreState != EU5_Attribute_RestoreState::Restore)
		return;

	StaminaModify(true, StaminaRestorePerSecondNormalized * 100 * DeltaTime);
	
	if (GetStamina() >= GetStaminaCapacity()) SetStaminaRestoreState(EU5_Attribute_RestoreState::None);
}

void UU5_CharacterBio_ACC::OnStaminaRestoreStateChanged(EU5_Attribute_RestoreState PrevState)
{
	switch (StaminaRestoreState)
	{
		case EU5_Attribute_RestoreState::None:
			GetWorld()->GetTimerManager().ClearTimer(StaminaRestoreCooldownTimerHandle);
			break;
		case EU5_Attribute_RestoreState::Cooldown:
			GetWorld()->GetTimerManager().SetTimer(StaminaRestoreCooldownTimerHandle, this, &UU5_CharacterBio_ACC::OnStaminaCooldownEnded, StaminaRestoreCooldown);
	}
}

float UU5_CharacterBio_ACC::HeatModify(bool _positive, float _value)
{
	Heat.Modify(_positive, _value);
	return Heat.Heat;
}

void UU5_CharacterBio_ACC::OnHeatChanged_Implementation(float _value, float _normalizedValue, float _incomingValue)
{
}


void UU5_CharacterBio_ACC::SetGenericTeamId(const FGenericTeamId& _teamId)
{
	TeamId = _teamId;
}

ETeamAttitude::Type UU5_CharacterBio_ACC::GetTeamAttitudeTowards(const AActor* _other) const
{
	if (!IsValid(_other)) return ETeamAttitude::Neutral;

	const AActor* otherActor = _other;
	if (const AController* otherController = Cast<AController>(otherActor)) 
		otherActor = otherController->GetPawn();

	UU5_CharacterBio_ACC* bioComponent = _other->FindComponentByClass<UU5_CharacterBio_ACC>();
	if (!bioComponent) return ETeamAttitude::Neutral;

	return TeamId.GetAttitude(GetGenericTeamId(), bioComponent->GetGenericTeamId());
}

void Attribute_Health::Modify(bool _positive, float _value)
{
	if(FMath::IsNearlyZero(_value)) return;
	
	(_positive) ? Health += _value : Health -= _value;
	Check_Internal();
}

float Attribute_Health::Get() const
{
	return Health;
}

void Attribute_Health::Check_Internal()
{
	if (Health < Limit.X)
	{
		This->OnDeathBecame();

		return;
	}

	Health = FGenericPlatformMath::Min(Health, Limit.Y);

	const float normalizedValue = FMath::GetRangePct<float, float>(Limit.X, Limit.Y, Health); 
	This->OnHealthChanged(Health, normalizedValue);
}

void Attribute_Stamina::ModifyStaminaValue(bool _positive, float _value)
{
	if(FMath::IsNearlyZero(_value)) return;
	
	(_positive) ? Stamina += _value : Stamina -= _value;
	UpdateStaminaValue();
}

void Attribute_Stamina::ModifyStaminaCapacity(bool _positive, float _value)
{
	if(FMath::IsNearlyZero(_value)) return;

	(_positive) ? Capacity += _value : Capacity -= _value;
	UpdateStaminaCapacity();
}

float Attribute_Stamina::GetStaminaValue() const
{
	return Stamina;
}

float Attribute_Stamina::GetStaminaCapacity() const
{
	return Capacity;
}

float Attribute_Stamina::GetNormalizedStaminaValue() const
{
	return FMath::GetRangePct<float, float>( CapacityLimit.X, Capacity, Stamina);
}

float Attribute_Stamina::GetNormalizedStaminaCapacity() const
{
	return FMath::GetRangePct<float, float>( CapacityLimit.X, CapacityLimit.Y, Capacity);
}

void Attribute_Stamina::UpdateStaminaValue()
{
	Stamina = FMath::Clamp(Stamina, 0.0f, Capacity);
	const float normalizedValue = GetNormalizedStaminaValue();
	This->OnStaminaChanged(Stamina, normalizedValue);
}

void Attribute_Stamina::UpdateStaminaCapacity()
{
	Capacity = FMath::Clamp(Capacity, CapacityLimit.X, CapacityLimit.Y);
	const float normalizedValue = GetNormalizedStaminaCapacity();
	This->OnStaminaCapacityChanged(Capacity, normalizedValue);
}

void UU5_CharacterBio_ACC::OnStaminaChanged_Implementation(float Value, float NormalizedValue)
{
}

void Attribute_Heat::Modify(bool _positive, float _value)
{
	const float multiplySign = _positive ? 1.0f : -1.0f;
	const float incomingValue = _value * multiplySign; 
	Heat += incomingValue;
	Check_Internal(incomingValue);
}

float Attribute_Heat::Get() const
{
	return Heat;
}

void Attribute_Heat::Check_Internal(float _incomingValue)
{
	Heat = FMath::Clamp(Heat, Limit.X, Limit.Y);

	const float normalizedValue = FMath::GetRangePct<float, float>( Limit.X, Limit.Y, Heat); 
	This->OnHeatChanged(Heat, normalizedValue, _incomingValue);
}

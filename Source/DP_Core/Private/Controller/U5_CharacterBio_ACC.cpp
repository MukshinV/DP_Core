#include "Controller/U5_CharacterBio_ACC.h"
#include "../Utils/U5_Utils.h"
#include "../Controller/U5_Behavior_ACC.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"

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
}

float UU5_CharacterBio_ACC::HeatModify(bool _positive, float _value)
{
	Heat.Modify(_positive, _value);
	return Heat.Heat;
}

void UU5_CharacterBio_ACC::OnHeatChanged_Implementation(float Value, float NormalizedValue)
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

void Attribute_Health::Modify(bool Positive, float Value)
{
	(Positive) ? Health += Value : Health -= Value;
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

void Attribute_Heat::Modify(bool Positive, float Value)
{
	(Positive) ? Heat += Value : Heat -= Value;
	Check_Internal();
}

float Attribute_Heat::Get() const
{
	return Heat;
}

void Attribute_Heat::Check_Internal()
{
	Heat = FMath::Clamp(Heat, Limit.X, Limit.Y);

	const float normalizedValue = FMath::GetRangePct<float, float>( Limit.X, Limit.Y, Heat); 
	This->OnHeatChanged(Heat, normalizedValue);
}

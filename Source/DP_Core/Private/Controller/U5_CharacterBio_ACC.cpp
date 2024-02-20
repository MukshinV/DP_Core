#include "../Utils/U5_Utils.h"
#include "../Controller/U5_Behavior_ACC.h"
#include "Controller/U5_CharacterBio_ACC.h"
#include "GenericPlatform/GenericPlatformMath.h"

float UU5_CharacterBio_ACC::HealthModify(bool Positive, float Value)
{
	Health.Modify(Positive, Value);
	return Health.Health;
}

void UU5_CharacterBio_ACC::OnHealthChange(float Value)
{
	
}

void UU5_CharacterBio_ACC::OnDeathBecame()
{
	cbDeath.Broadcast();
	OnDeath();
	UU5_Behavior_ACC* beh = GetOwner()->FindComponentByClass<UU5_Behavior_ACC>();
	if (beh)
	{
		beh->Report_OnThisBehaviorspawnIsDead();
	}
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
	This->OnHealthChange(Health);
}

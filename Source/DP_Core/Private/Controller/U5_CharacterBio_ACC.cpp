
#include "Controller/U5_CharacterBio_ACC.h"
#include "../Utils/U5_Utils.h"


void UU5_CharacterBio_ACC::HealthModify(bool Positive, float Value)
{
	Health.Modify(Positive, Value);
}

void UU5_CharacterBio_ACC::OnHealthChange(float Value)
{

}

void UU5_CharacterBio_ACC::OnDeathBecame()
{
	cbDeath.Broadcast();
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
	Positive ? Health += Value : Health -= Value;
	Check_Internal();
}

float Attribute_Health::Get() const
{
	return Health;
}

void Attribute_Health::Check_Internal()
{
	if (Health <= Limit.X)
	{
		mU5_DEBUGOUT(true, GetOwner() << "Is Dead!");
	}
}

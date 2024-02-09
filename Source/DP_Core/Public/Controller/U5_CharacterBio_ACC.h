
#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GenericTeamAgentInterface.h"

#include "U5_CharacterBio_ACC.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DP_CORE_API UU5_CharacterBio_ACC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UU5_CharacterBio_ACC() {}


public: // Attributes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@Health"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@HealthLimits"))
	FVector2D HealthLimits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@Stamina"))
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@StaminaLimits"))
	FVector2D StaminaLimits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@Heat"))
	float Heat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@HeatLimits"))
	FVector2D HeatLimits;

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

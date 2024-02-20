
#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GenericTeamAgentInterface.h"

#include "U5_CharacterBio_ACC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

class UU5_CharacterBio_ACC;

class Attribute_Health
{
	UU5_CharacterBio_ACC* This;
	UU5_CharacterBio_ACC* GetOwner() { return This; }

public:
	Attribute_Health() : This(nullptr) {}
	Attribute_Health(UU5_CharacterBio_ACC* _this) { This = _this; }

public: // Health
	UPROPERTY(VisibleAnywhere, DisplayName="@Health")
	float Health = 100;

	UPROPERTY(VisibleAnywhere, DisplayName = "@HealthLimit")
	FVector2D Limit { 0, 100 };

	UFUNCTION(BlueprintCallable, DisplayName="!HealthModify(C, Virtual)")
	void Modify(bool Positive, float Value);

	UFUNCTION(BlueprintCallable, DisplayName="!HealthGet(C, Virtual)")
	float Get() const ;

private:
	void Check_Internal();
};

UCLASS(Blueprintable)
class DP_CORE_API UU5_CharacterBio_ACC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UU5_CharacterBio_ACC() : Health(this) 
	{
		PrimaryComponentTick.bCanEverTick = false;
	}


public: // Attribute Health

	Attribute_Health Health;

	UFUNCTION(BlueprintCallable, DisplayName="!HealthModify(C, Virtual)")
	float HealthModify(bool Positive, float Value);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetHealth(C, Virtual)")
	float GetHealth() const { return Health.Get(); }

	void OnHealthChange(float Value);
	void OnDeathBecame();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FDeathDelegate cbDeath;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="!OnDeath(Virtual)")
	void OnDeath();


public: // Attribute Stamina

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@Stamina"))
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@StaminaLimits"))
	FVector2D StaminaLimits;

public: // Attribute Heat

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@Heat"))
	float Heat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "@HeatLimits"))
	FVector2D HeatLimits;

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

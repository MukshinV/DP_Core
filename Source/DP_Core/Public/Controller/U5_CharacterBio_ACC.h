
#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GenericTeamAgentInterface.h"

#include "U5_CharacterBio_ACC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

class UU5_CharacterBio_ACC;

class Attribute_Health
{
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
	float Get() const;

private:
	UPROPERTY()
	UU5_CharacterBio_ACC* This;
	
	void Check_Internal();
	UU5_CharacterBio_ACC* GetOwner() const { return This; }
};

class Attribute_Heat
{
public:
	Attribute_Heat() : This(nullptr) {}
	Attribute_Heat(UU5_CharacterBio_ACC* _this) { This = _this; }

public: // Heat
	UPROPERTY(VisibleAnywhere, DisplayName="@Heat")
	float Heat = 100;

	UPROPERTY(VisibleAnywhere, DisplayName = "@HeatLimit")
	FVector2D Limit { 0, 100 };

	UFUNCTION(BlueprintCallable, DisplayName="!HeatModify(C, Virtual)")
	void Modify(bool Positive, float Value);

	UFUNCTION(BlueprintCallable, DisplayName="!HeatGet(C, Virtual)")
	float Get() const;

private:
	UPROPERTY()
	UU5_CharacterBio_ACC* This;
	
	UU5_CharacterBio_ACC* GetOwner() const { return This; }
	void Check_Internal();
};

UCLASS(Blueprintable)
class DP_CORE_API UU5_CharacterBio_ACC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UU5_CharacterBio_ACC() :
		Health(this),
		Heat(this)
	{
		PrimaryComponentTick.bCanEverTick = false;
	}


public: // Death
	UFUNCTION(BlueprintPure, DisplayName = "!IsDead()", Category = "Death")
	FORCEINLINE bool IsDead() const { return bDead; }

protected:
	bool bDead{ false };


public: // Attribute Health

	Attribute_Health Health;

	UFUNCTION(BlueprintCallable, DisplayName="!HealthModify(C, Virtual)")
	virtual float HealthModify(bool _positive, float _value);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetHealth(C, Virtual)")
	virtual float GetHealth() const { return Health.Get(); }

	UFUNCTION(BlueprintNativeEvent, DisplayName="!OnHealthChanged(Virtual)")
	void OnHealthChanged(float Value, float NormalizedValue);

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

	Attribute_Heat Heat;

	UFUNCTION(BlueprintCallable, DisplayName="!HeatModify(C, Virtual)")
	virtual float HeatModify(bool _positive, float _value);

	UFUNCTION(BlueprintCallable, DisplayName = "!GetHeat(C, Virtual)")
	virtual float GetHeat() const { return Heat.Get(); }

	UFUNCTION(BlueprintCallable, DisplayName = "!GetHeatLimits(C)")
	FVector2D GetHeatLimits() const { return Heat.Limit; }

	UFUNCTION(BlueprintNativeEvent, DisplayName="!OnHeatChanged(Virtual)")
	void OnHeatChanged(float Value, float NormalizedValue);

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

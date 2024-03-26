
#pragma once

#include "CoreMinimal.h"
#include "EventSystem/U5_AreaEvent_CA.h"
#include "U5_AreaWeather_CA.generated.h"

UCLASS(Blueprintable)
class DP_CORE_API AU5_AreaWeather_CA : public AU5_AreaEvent_CA
{
	GENERATED_BODY()
public:
	AU5_AreaWeather_CA();

#if WITH_EDITOR
	virtual void MakeActive() override;
	virtual void SwitchOff() override;
#endif
};

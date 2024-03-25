#include "WeatherSystem/U5_AreaWeather_CA.h"

#include "U5_LevelWeather_CA.h"
#include "Kismet/GameplayStatics.h"

AU5_AreaWeather_CA::AU5_AreaWeather_CA()
{
	PrimaryActorTick.bCanEverTick = false;
}

#if WITH_EDITOR

void AU5_AreaWeather_CA::MakeActive()
{
	Super::MakeActive();

	AActor* levelWeather = UGameplayStatics::GetActorOfClass(this, AU5_LevelWeather_CA::StaticClass());
	if(levelWeather)
	{
		Cast<AU5_LevelWeather_CA>(levelWeather)->SetWeatherSource(this);
	}
}

void AU5_AreaWeather_CA::SwitchOff()
{
	Super::SwitchOff();

	AActor* levelWeather = UGameplayStatics::GetActorOfClass(this, AU5_LevelWeather_CA::StaticClass());
	if(levelWeather)
	{
		Cast<AU5_LevelWeather_CA>(levelWeather)->SetFXVisibility(true);
	}
}

#endif

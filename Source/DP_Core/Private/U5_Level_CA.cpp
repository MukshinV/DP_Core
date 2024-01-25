#include "U5_Level_CA.h"
#include "../UnrealCore/U5_GameInstace.h"
#include "Kismet/GameplayStatics.h"

void AU5_Level_CA::BeginPlay()
{
	Super::BeginPlay();
}

void AU5_Level_CA::EndPlay(EEndPlayReason::Type _reason)
{
	UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (gameInstance)
	{
		gameInstance->UnRegisterLevelActor(this);
	}

	Super::EndPlay(_reason);
}

void AU5_Level_CA::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	RegisterActorInGI_Internal();
}


void AU5_Level_CA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AU5_Level_CA::RegisterActorInGI_Internal()
{
	UU5_GameInstance* gameInstance = Cast<UU5_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (gameInstance)
	{
		gameInstance->RegisterLevelActor(this);
	}
}


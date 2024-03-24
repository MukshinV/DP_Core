// Fill out your copyright notice in the Description page of Project Settings.


#include "U5_Area_GI_CU.h"

#include "U5_LevelWeather_CA.h"
#include "Net/UnrealNetwork.h"
#include "Utils/U5_Utils.h"

UU5_Area_GI_CU::UU5_Area_GI_CU()
{
}

void UU5_Area_GI_CU::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UU5_Area_GI_CU, CurrentArea)
}

void UU5_Area_GI_CU::PushArea(AU5_AreaEvent_CA* _areaActor)
{
	AreasArray.Insert(_areaActor, 0);
	CurrentArea = _areaActor;
}

void UU5_Area_GI_CU::RemoveArea(AU5_AreaEvent_CA* _areaActor)
{
	AreasArray.Remove(_areaActor);

	if(AreasArray.Num() > 0)
	{
		if(AreasArray[0] != CurrentArea)
		{
			CurrentArea = AreasArray[0];
		}
		
		return;
	}

	CurrentArea = nullptr;
}

void UU5_Area_GI_CU::SetCurrentArea(AU5_AreaEvent_CA* _areaActor)
{
	CurrentArea = _areaActor;
}

void UU5_Area_GI_CU::OnCurrentAreaChanged()
{
#if U5_DEBUG_ENABLE
	if(!CurrentArea)
	{
		mU5_DEBUGOUT(true, L"Area changed: NULL");
	}
	else
	{
		mU5_DEBUGOUT(true, L"Area changed: " << mDNAME(CurrentArea))
	}
#endif

	AU5_LevelWeather_CA* weatherActor = Cast<AU5_LevelWeather_CA>(GetLevelActor());
	if(!weatherActor) return;

	weatherActor->SetWeatherSource(CurrentArea);
}

void UU5_Area_GI_CU::TravelTo_Implementation(const FDataTableRowHandle& _levelToGo)
{
}

void UU5_Area_GI_CU::OnRep_CurrentArea()
{
	OnCurrentAreaChanged();
}
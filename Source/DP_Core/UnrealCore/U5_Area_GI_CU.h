// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_GameInstace.h"
#include "U5_Travel_CI.h"
#include "EventSystem/U5_AreaEvent_CA.h"
#include "UObject/Object.h"
#include "U5_Area_GI_CU.generated.h"

UCLASS()
class DP_CORE_API UU5_Area_GI_CU : public UU5_GameInstance, public IU5_Travel_CI
{
	GENERATED_BODY()

public:
	UU5_Area_GI_CU();
	
	UFUNCTION(BlueprintCallable, DisplayName="!PushArea(C, Virtual)(U5_AreaEvent_CA)")
	virtual void PushArea(AU5_AreaEvent_CA* _areaActor);
	UFUNCTION(BlueprintCallable, DisplayName="!RemoveArea(C, Virtual)(U5_AreaEvent_CA)")
	virtual void RemoveArea(AU5_AreaEvent_CA* _areaActor);
	UFUNCTION(BlueprintCallable, DisplayName="!SetCurrentArea(C, Virtual)(U5_AreaEvent_CA)")
	virtual void SetCurrentArea(AU5_AreaEvent_CA* _areaActor);
	UFUNCTION(BlueprintCallable, DisplayName="!OnCurrentAreaChanged(C, Virtual)()")
	virtual void OnCurrentAreaChanged();
	
	virtual void TravelTo_Implementation(const FDataTableRowHandle& _levelToGo) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@AreasArray")
	TArray<AU5_AreaEvent_CA*> AreasArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="@CurrentArea")
	TObjectPtr<AU5_AreaEvent_CA> CurrentArea;
};

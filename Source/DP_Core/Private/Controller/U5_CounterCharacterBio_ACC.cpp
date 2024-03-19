// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/U5_CounterCharacterBio_ACC.h"


void UU5_CounterCharacterBio_ACC::OnDeathBecame()
{
	if (HasHealthBars())
	{
		UpdateHealthBar();
	}
	else
	{
		Super::OnDeathBecame();
	}
}

void UU5_CounterCharacterBio_ACC::UpdateHealthBar()
{
	Health.Reset();
	HealthBarCount++;
	cbHealthBarChangedDelegate.Broadcast(HealthBarCount);
}

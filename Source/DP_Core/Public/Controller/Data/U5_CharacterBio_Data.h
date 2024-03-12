// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "U5_CharacterBio_Data.generated.h"


UENUM(BlueprintType)
enum class EU5_Attribute_RestoreState : uint8
{
	None,
	Cooldown,
	Restore
};

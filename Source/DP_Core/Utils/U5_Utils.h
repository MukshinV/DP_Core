// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "U5_Utils.generated.h"

/**
 * Global utils for the U5 plugin
 */

#define U5_DO_DEBUG_LOG 1

#define mDEVMSG(text)	std::cout<<text
#define mQUOTED(text)	" ["	## text ##		"] "
#define mSPASED(text)	" "		## text ##		" "
#define mBRACED(text)	" <"	## text ##		"> "
#define mDBRACED(text)	" <<"	## text ##		">> "
#define mSBRACED(text)	" ["	## text ##		"] "
#define mRBRACED(text)	" ("	## text ##		") "
#define mQBRACED(text)	' "'	## text ##		'" '

UCLASS()
class DP_CORE_API U5 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void SelfCheckModule();

	UFUNCTION()
	static void Log(const FString& _value);

	UFUNCTION()
	static void Message(const FString& _message);

	UFUNCTION()
	static void DebugMessage(const FString& _message)
	{ if (U5_DO_DEBUG_LOG) { U5::Message(_message); } else return; }

	UFUNCTION()
	static void RegisterError(const FString& _error);

	UFUNCTION()
	static void RegisterCriticalError(const FString& _error);

	UFUNCTION()
	static void RegisterWarning(const FString& _error);

};

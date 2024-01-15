#pragma once
///! Global utils for the U5 plugin.
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "U5_Utils.generated.h"

#define U5_DO_DEBUG_LOG 1
#ifndef U5_DEBUG_ENABLE
#define U5_DEBUG_ENABLE U5_DO_DEBUG_LOG
#endif

#define mDEVMSG(text)	std::cout<<text
#define mQUOTED(text)	" ["	## text ##		"] "
#define mSPASED(text)	" "		## text ##		" "
#define mBRACED(text)	" <"	## text ##		"> "
#define mDBRACED(text)	" <<"	## text ##		">> "
#define mSBRACED(text)	" ["	## text ##		"] "
#define mRBRACED(text)	" ("	## text ##		") "
#define mQBRACED(text)	' "'	## text ##		'" '

// TODO: FString strean or use standart tchar stream. printf style is kiiling me.
#define mU5_FUNCTION(enable, text) { if (enable && U5_DO_DEBUG_LOG && U5_DEBUG_ENABLE) U5::DebugMessage ( FString( __func__ ) + TEXT(text) ); }
#define mU5_DEBUGOUT(enable, text) { if(enable){U5::DebugMessage(text);} }

UCLASS()
class DP_CORE_API U5_EasyLogInterface : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void SelfCheckModule();

	UFUNCTION()
	static void Log(const FString& _value);

	UFUNCTION()
	static void Message(const FString& _message);

	UFUNCTION()
	static void DebugMessage(const FString& _message);

	UFUNCTION()
	static void RegisterError(const FString& _error);

	UFUNCTION()
	static void RegisterCriticalError(const FString& _error);

	UFUNCTION()
	static void RegisterWarning(const FString& _error);

};

UCLASS()
class DP_CORE_API U5 : public U5_EasyLogInterface
{
	GENERATED_BODY()
};

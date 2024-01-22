// Copyright Epic Games, Inc. All Rights Reserved.

#include "DP_Core.h"
#include "Utils/U5_Utils.h"

#define LOCTEXT_NAMESPACE "FDP_CoreModule"

void FDP_CoreModule::StartupModule()
{
	mU5_FUNCTION(true);
	mU5_FUNCMESS(true, mQUOTED("Func") << " message " << "log. " << "DP_Core module started.");
	mU5_FUNCMESS(false, mSBRACED("This func message log shouldn't be visible in log."));
	mU5_DEBUGOUT(true, mBRACED("Debug") << " message " << "log. " << "DP_Core module started.");
	mU5_DEBUGOUT(false, mSBRACED("This debug message shouldn't be visible in log."));
}

void FDP_CoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDP_CoreModule, DP_Core)
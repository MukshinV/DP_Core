// Fill out your copyright notice in the Description page of Project Settings.

#include "U5_Utils.h"

void U5_EasyLogInterface::SelfCheckModule()
{
	GLog->Log("Module is OK!");
}

void U5_EasyLogInterface::Log(const FString& _value)
{
	GLog->Log(_value);
}

void U5_EasyLogInterface::Message(const FString& _message)
{
	Log(_message);
}

void U5_EasyLogInterface::RegisterError(const FString& _error)
{
}

void U5_EasyLogInterface::RegisterCriticalError(const FString& _error)
{
}

void U5_EasyLogInterface::RegisterWarning(const FString& _error)
{
}

void U5_EasyLogInterface::DebugMessage(const FString& _message)
{
	if (U5_DO_DEBUG_LOG) 
	{
		U5::Message(TEXT(">> U5 Debug: ") + _message); 
	}
	else return;
}

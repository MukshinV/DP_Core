// Fill out your copyright notice in the Description page of Project Settings.

#include "U5_Utils.h"

void U5::SelfCheckModule()
{
	GLog->Log("Module is OK!");
}

void U5::Log(const FString& _value)
{
	GLog->Log(_value);
}

void U5::Message(const FString& _message)
{
	Log(_message);
}

void U5::RegisterError(const FString& _error)
{
}

void U5::RegisterCriticalError(const FString& _error)
{
}

void U5::RegisterWarning(const FString& _error)
{
}

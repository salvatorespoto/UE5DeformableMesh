// Copyright Epic Games, Inc. All Rights Reserved.

#include "RayMarchingModule.h"

#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "ShaderCore.h"

#define LOCTEXT_NAMESPACE "FRayMarchingModule"

void FRayMarchingModule::StartupModule()
{
	
}

void FRayMarchingModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRayMarchingModule, RayMarching)
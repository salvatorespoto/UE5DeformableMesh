// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class RayMarchingModule : ModuleRules
{
	public RayMarchingModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] 
			{
				// TODO check this is needed
				Path.Combine(GetModuleDirectory("Renderer"), "Private"),
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] 
			{
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[] 
			{
				"Engine"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// TODO check all the dependency are actually used
				"Core",
				"CoreUObject",
				"Engine",
				"RHI",
				"Renderer",
				"Projects",
				"RenderCore",
				"Slate",
				"SlateCore",
			}
			);
		
		// TODO check this is nedeed
		if (Target.Type == TargetType.Editor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
			PrivateDependencyModuleNames.Add("EditorWidgets");
		}
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}

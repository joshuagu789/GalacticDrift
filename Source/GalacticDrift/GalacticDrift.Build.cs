// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GalacticDrift : ModuleRules
{
	public GalacticDrift(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}

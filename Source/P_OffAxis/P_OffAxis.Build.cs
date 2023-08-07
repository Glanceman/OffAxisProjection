// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class P_OffAxis : ModuleRules
{
	public P_OffAxis(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}

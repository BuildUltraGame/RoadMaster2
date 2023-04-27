// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RoadMaster2 : ModuleRules
{
	public RoadMaster2(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AdvancedSessions" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput","UMG" });
    }
}

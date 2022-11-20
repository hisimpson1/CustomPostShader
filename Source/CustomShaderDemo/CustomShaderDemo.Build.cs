// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CustomShaderDemo : ModuleRules
{
	public CustomShaderDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
            //SHADER EDIT START
            "RHI",
            "RenderCore"             
            //SHADER EDIT END
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            //SHADER EDIT START
             "Projects",
             //SHADER EDIT END
        });
    }
}

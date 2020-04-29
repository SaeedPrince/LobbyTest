// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class LobbyTest : ModuleRules
{
	public LobbyTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "OnlineSubsystem", "OnlineSubsystemUtils" });

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "HeadMountedDisplay" , "SteamVR" });

		PrivateDependencyModuleNames.Add("OnlineSubsystem");
	}
}

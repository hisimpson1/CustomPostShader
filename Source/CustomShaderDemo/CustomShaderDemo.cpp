// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomShaderDemo.h"
#include "Modules/ModuleManager.h"

//SHADER EDIT START ~ SHADER EDIT End 이라인을 주석 처리 한다.
//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, CustomShaderDemo, "CustomShaderDemo" );
 
//SHADER EDIT START

#include "Misc/Paths.h"
#include "ShaderCore.h"


// DEFAULT - Created by default with new project - We will change FDefaultGameModuleImpl with our custom module which add the shader folder
/*
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, CustomShaderDemo, "CustomShaderDemo" );
*/

//IMPLEMENT_MODULE(FThisModuleAddsaVirtualShaderFolderModule, CustomShaderDemo) 

// OR

//위의 라인으로 빌드 하면 Shipping에서 빌드시 링크 에러가 발생한다.
IMPLEMENT_PRIMARY_GAME_MODULE(FThisModuleAddsaVirtualShaderFolderModule, CustomShaderDemo, "CustomShaderDemo");



void FThisModuleAddsaVirtualShaderFolderModule::StartupModule()
{
	// Find the static location of the shader folder on your computer
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));


	////////////////////////
	// Define the name you will use in the engine to access this folder
	//
	// FORMALISM SUGGESTION: 
	// 
	// linking from a project: TEXT("/Project/YourProjectName")
	// linking from a plugin: TEXT("/Plugin/YourPluginName")

	AddShaderSourceDirectoryMapping(TEXT("/Project"), ShaderDirectory);  //Shaders 폴더가 만들어져 있지 않으면 크래쉬 된다. //DDD

	///////////////////////


}

void FThisModuleAddsaVirtualShaderFolderModule::ShutdownModule()
{
	//Users reported it might solve linking issues - haven't had the need myself
	//ResetAllShaderSourceDirectoryMappings();
}


//SHADER EDIT END
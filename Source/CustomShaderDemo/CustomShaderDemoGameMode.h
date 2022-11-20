// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomShaderDemoGameMode.generated.h"

UCLASS(minimalapi)
class ACustomShaderDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACustomShaderDemoGameMode();
	virtual void StartPlay() override;
	void SetColorInCustomNode();

	virtual void Tick(float DeltaTime) override;
};




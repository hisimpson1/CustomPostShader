// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomShaderDemoGameMode.h"
#include "CustomShaderDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

//DrawBound EDIT START
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"

#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

#include "EngineUtils.h" //TActorIterator
//DrawBound EDIT END

#include "TestPostEffect.h"

#pragma optimize( "", off )

ACustomShaderDemoGameMode::ACustomShaderDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
}

void ACustomShaderDemoGameMode::StartPlay()
{
	Super::StartPlay();

#if  0
	GetWorld()->SpawnActor<ATestPostEffect>(ATestPostEffect::StaticClass());
#else
	FName Path = TEXT("Blueprint'/Game/blueprint/Post_BP.Post_BP_C'");
	UClass* GeneratedBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	GetWorld()->SpawnActor<AActor>(GeneratedBP);
	/*
	FActorSpawnParameters spawnParams;
	FRotator rotator;
	FVector spawnLocation = FVector::ZeroVector;
	GetWorld()->SpawnActor<AActor>(GeneratedBP, spawnLocation, rotator, spawnParams);
	*/
#endif

	SetColorInCustomNode();
}

void ACustomShaderDemoGameMode::Tick(float DeltaTime)
{
}

void ACustomShaderDemoGameMode::SetColorInCustomNode()
{
	AActor* pTargetActor = nullptr;
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("CustomMat")), ActorList);
	
	for (int n = 0; n < ActorList.Num(); ++n)
	{
		if (ActorList[n]->GetName().Contains(TEXT("Sphere")))
		{
			//DDD
			UStaticMeshComponent* StaticMeshComponent = ActorList[n]->FindComponentByClass<UStaticMeshComponent>();
			UMaterialInterface* Mat = StaticMeshComponent->GetMaterial(0);
			if (Mat->GetName() != TEXT("redhlsl_mat"))
				break;

			FVector ChangeColor = FVector(0.0f, 1.0f, 0.0f);

			UMaterialInstanceDynamic* matInstance = StaticMeshComponent->CreateDynamicMaterialInstance(0, Mat);
			if (matInstance != nullptr)
				matInstance->SetVectorParameterValue(FName(TEXT("RGBColor")), ChangeColor);

			UE_LOG(LogTemp, Log, TEXT("Have Tag"));
			break;
		}
	}
}



#pragma optimize( "", on ) 
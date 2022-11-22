// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPostEffect.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Engine/PostProcessVolume.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#pragma optimize( "", off )
// Sets default values
ATestPostEffect::ATestPostEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//동적으로 로딩하는 경우 비쥬얼스튜디오가 없는곳에서는 *.ush 파일이 로딩이 안되는 문제가 있다.
	/*
	ConstructorHelpers::FObjectFinder<UMaterialInstance> PostMatInstRes(TEXT("MaterialInstanceConstant'/Game/Material/test_post_Inst.test_post_Inst'"));
	if (PostMatInstRes.Succeeded())
	{
		PostMatInst = PostMatInstRes.Object;
	}
	*/
}

// Called when the game starts or when spawned
void ATestPostEffect::BeginPlay()
{
	Super::BeginPlay();
	
	AddPostEffect();
}

// Called every frame
void ATestPostEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestPostEffect::AddPostEffect()
{
	if (PostMat == nullptr)
		return;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, APostProcessVolume::StaticClass(), Actors);

	if (Actors.Num() > 0)
	{
		APostProcessVolume* PostProcess = Cast<APostProcessVolume>(Actors[0]);
		if (PostProcess)
		{
			PostDynamicMat = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), PostMat);
			FPostProcessSettings& PostProcessSettings = PostProcess->Settings;
			FWeightedBlendable WeightedBlendable;
			WeightedBlendable.Object = PostDynamicMat;
			WeightedBlendable.Weight = 1;
			PostProcessSettings.WeightedBlendables.Array.Add(WeightedBlendable);

			PostProcessPtr = PostProcess;
		}
	}
}

void ATestPostEffect::RemovePostEffect()
{
	if (PostMat == nullptr)
		return;

	APostProcessVolume* PostProcess = PostProcessPtr.Get();
	if (PostProcess == nullptr)
		return;

	FPostProcessSettings& PostProcessSettings = PostProcess->Settings;
	for (int n = 0; n < PostProcessSettings.WeightedBlendables.Array.Num(); ++n)
	{
		if(PostProcessSettings.WeightedBlendables.Array[n].Object->GetName() == PostDynamicMat->GetName())
		{
			PostProcessSettings.WeightedBlendables.Array.RemoveAt(n);
			break;
		}
	}
}

#pragma optimize( "", on )
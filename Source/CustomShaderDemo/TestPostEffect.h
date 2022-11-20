// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestPostEffect.generated.h"

UCLASS()
class CUSTOMSHADERDEMO_API ATestPostEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestPostEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void AddPostEffect();
	void RemovePostEffect();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	//class UMaterialInstance* PostMatInst;
	class UMaterial* PostMatInst;
	UPROPERTY()
	class UMaterialInstanceDynamic* PostDynamicMat;

	TWeakObjectPtr<class APostProcessVolume> PostProcessPtr;
};

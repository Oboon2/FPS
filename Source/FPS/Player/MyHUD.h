// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UTexture2D* Crosshair;
};

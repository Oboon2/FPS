// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "MyPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AMyPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	

public:
	virtual void UpdateCamera(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float NormalFOV = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float IronsightFOV = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float NormalCameraZ = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CrouchCameraZ = -48.0f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsRunning = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Yaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsCrouched = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsIronsight = false;

	UPROPERTY(BlueprintReadWrite)
		bool bIsFalling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float FireAlpha = 0;

	UPROPERTY(BlueprintReadWrite)
		float AimYaw;

	UPROPERTY(BlueprintReadWrite)
		float AimPitch;

	UFUNCTION()
		void AnimNotify_HelloWorld(UAnimNotify * Notify);

	UFUNCTION()
		void AnimNotify_MoveLock(UAnimNotify * Notify);

	UFUNCTION()
		void AnimNotify_MoveUnlock(UAnimNotify * Notify);

	UFUNCTION()
		void AnimNotify_DeadDestroy(UAnimNotify * Notify);
};
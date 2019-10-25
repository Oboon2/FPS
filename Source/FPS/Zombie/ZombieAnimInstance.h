// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Zombie.h"

#include "ZombieAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EZombieState CurrentState = EZombieState::Normal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;
	
};

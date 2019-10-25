// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;
};

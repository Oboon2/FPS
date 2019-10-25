// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGM.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ABattleGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleGM();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AMasterItem> ItemClass;

	
};

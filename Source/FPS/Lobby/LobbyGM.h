// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGM.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ALobbyGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void LeftTimer();

	FTimerHandle LeftTimerHandle;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	void GameStart();
};

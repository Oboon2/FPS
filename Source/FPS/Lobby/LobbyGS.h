// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGS.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ALobbyGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
		int LeftTime = 60;
	UPROPERTY(ReplicatedUsing="ConnectCount_OnRep")
		int ConnectCount = 0;

	ALobbyGS();

	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
		void ConnectCount_OnRep();
};

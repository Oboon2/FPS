// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ULobbyWidgetBase> LobbyWidgetClass;

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class ULobbyWidgetBase* LobbyWidget;


	UFUNCTION(Server, Reliable, WithValidation)
		void C2S_SendMessage(const FText& Message);
		bool C2S_SendMessage_Validate(const FText& Message);
		void C2S_SendMessage_Implementation(const FText& Message);

	UFUNCTION(Client, Reliable)
		void S2C_SendMessage(const FText& Message);
		void S2C_SendMessage_Implementation(const FText& Message);
};

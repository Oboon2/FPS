// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ULobbyWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UTextBlock* AliveCount;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UTextBlock* PublicMessage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UScrollBox* ChattingBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UEditableTextBox* ChatBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UButton* GameStartButton;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void GameStart();
	UFUNCTION(BlueprintCallable)
		void OnTextCommit(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION(BlueprintCallable)
		void AddMessage(const FText& Text);
	UFUNCTION(BlueprintCallable)
		void SetLifeTime(int32 LeftTime);
	UFUNCTION(BlueprintCallable)
		void SetConnectCount(int32 Count);
	UFUNCTION(BlueprintNativeEvent)
		void PlayStartButton();
		void PlayStartButton_Implementation();

};

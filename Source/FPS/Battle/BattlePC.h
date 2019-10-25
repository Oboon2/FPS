// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattlePC.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ABattlePC : public APlayerController
{
	GENERATED_BODY()
public:
	ABattlePC();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UItemTipWidgetBase* ItemToolTip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UItemTipWidgetBase> ItemToolTipClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventoryWidgetBase* InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UInventoryWidgetBase> InventoryWidgetClass;

	void ShowItemName(FString Name);
	void HideItemName();

	void ShowInventory();
	void HideInventory();

	virtual void SetupInputComponent() override;
	void Inventory();
};

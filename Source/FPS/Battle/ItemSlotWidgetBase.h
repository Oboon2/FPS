// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemTable.h"
#include "ItemSlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UItemSlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBorder* ItemThumbnail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTextBlock* ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTextBlock* ItemCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UButton* ItemButton;

	virtual void NativeConstruct() override;

	void SetItem(FItemTable ItemData);

	UFUNCTION()
	void ItemUse();

	FItemTable CurrentItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		uint8 bUsed : 1;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};

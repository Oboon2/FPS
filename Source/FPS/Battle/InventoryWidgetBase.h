// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemTable.h"
#include "InventoryWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	// 스크롤 박스에 이미 생성된 위젯 리스트
	TArray<class UItemSlotWidgetBase*> ItemSlots;

	// 빈슬롯 찾는 함수
	UFUNCTION(BlueprintCallable)
	int32 GetEmptySlot() const;

	// 사용중인 슬롯 비우기
	UFUNCTION(BlueprintCallable)
	void SetEmptySlot(int32 Index);


	// 슬롯에 아이템 넣기
	UFUNCTION(BlueprintCallable)
	void SetItemSlot(int32 Index, FItemTable ItemData);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UScrollBox* ItemScroll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBorder* CharacterPreview;

	virtual void NativeConstruct() override;
};

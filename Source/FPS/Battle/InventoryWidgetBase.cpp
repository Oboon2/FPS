// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidgetBase.h"
#include "Components/Border.h"
#include "Components/ScrollBox.h"
#include "Battle/ItemSlotWidgetBase.h"

int32 UInventoryWidgetBase::GetEmptySlot() const
{
	for (int i = 0; i < ItemSlots.Num(); ++i)
	{
		if (ItemSlots[i]->bUsed == false)
		{
			return i;
		}
	}
	return -1;
}

void UInventoryWidgetBase::SetEmptySlot(int32 Index)
{
	if (Index < 0 || Index >ItemSlots.Num())
	{
		return;
	}
	ItemSlots[Index]->bUsed = false;
	ItemSlots[Index]->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryWidgetBase::SetItemSlot(int32 Index, FItemTable ItemData)
{
	if (Index < 0 || Index >ItemSlots.Num())
	{
		return;
	}
	ItemSlots[Index]->bUsed = true;
	ItemSlots[Index]->SetItem(ItemData);
	ItemSlots[Index]->SetVisibility(ESlateVisibility::Visible);
}
// 캐릭터 프리뷰 세팅
// 아이템 스크롤의 자식 탐색 후에 아이템 슬롯 배열에 연결
void UInventoryWidgetBase::NativeConstruct()
{
	CharacterPreview = Cast<UBorder>(GetWidgetFromName(TEXT("CharacterPreview")));
	ItemScroll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ItemScroll")));
	if (ItemScroll)
	{
		for (int i = 0; i < ItemScroll->GetChildrenCount(); ++i)
		{
			UItemSlotWidgetBase* ItemSlotWidget = Cast<UItemSlotWidgetBase>(ItemScroll->GetChildAt(i));
			if (ItemSlotWidget)
			{
				ItemSlots.Add(ItemSlotWidget);
				ItemSlotWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

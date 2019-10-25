// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidgetBase.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"

void UItemSlotWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	ItemThumbnail = Cast<UBorder>(GetWidgetFromName(TEXT("ItemThumbnail")));
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	ItemButton = Cast<UButton>(GetWidgetFromName(TEXT("ItemButton")));
	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UItemSlotWidgetBase::ItemUse);
	}
	bUsed = false;
}

void UItemSlotWidgetBase::SetItem(FItemTable ItemData)
{
	CurrentItemData = ItemData;
	FStreamableManager Loader;
	UTexture2D* T_ItemThumbnail = Loader.LoadSynchronous<UTexture2D>(CurrentItemData.ItemThumnail);
	ItemThumbnail->SetBrushFromTexture(T_ItemThumbnail);

	ItemName->SetText(FText::FromString(ItemData.ItemName));
	ItemCount->SetText(FText::FromString(FString::FromInt(ItemData.ItemCount)));
}

void UItemSlotWidgetBase::ItemUse()
{
	bUsed = false;
	SetVisibility(ESlateVisibility::Collapsed);
}

FReply UItemSlotWidgetBase::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		ItemUse();
	}
	return FReply::Handled();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTipWidgetBase.h"
#include "Components/TextBlock.h"

void UItemTipWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
}

void UItemTipWidgetBase::SetItemName(FString Name)
{
	if (ItemName)
	{
		ItemName->SetText(FText::FromString(Name));
	}
}

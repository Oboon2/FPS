// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePC.h"
#include "Player/MyPlayerCameraManager.h"
#include "Battle/ItemTipWidgetBase.h"
#include "Battle/InventoryWidgetBase.h"

ABattlePC::ABattlePC()
{
	PlayerCameraManagerClass = AMyPlayerCameraManager::StaticClass();
}

void ABattlePC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (ItemToolTipClass)
		{
			ItemToolTip = CreateWidget<UItemTipWidgetBase>(this, ItemToolTipClass);
			ItemToolTip->AddToViewport();
			ItemToolTip->SetVisibility(ESlateVisibility::Collapsed);
		}
		if (InventoryWidgetClass)
		{
			InventoryWidget = CreateWidget<UInventoryWidgetBase>(this, InventoryWidgetClass);
			InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

}

void ABattlePC::ShowItemName(FString Name)
{
	if (ItemToolTip) 
	{
		ItemToolTip->SetItemName(Name);
		ItemToolTip->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABattlePC::HideItemName()
{
	if (ItemToolTip)
	{
		ItemToolTip->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ABattlePC::ShowInventory()
{
	InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}

void ABattlePC::HideInventory()
{
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}

void ABattlePC::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &ABattlePC::Inventory);
}
void ABattlePC::Inventory()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		HideInventory();
	}
	else
	{
		ShowInventory();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTipWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UItemTipWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	int a;
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTextBlock* ItemName;

	UFUNCTION(BlueprintCallable)
	void SetItemName(FString Name);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// HTTP ¸ðµâ
#include "Http.h"
#include "IHttpRequest.h"
#include "IHttpResponse.h"

#include "TitleWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UTitleWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UEditableTextBox* UserID;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UEditableTextBox* Password;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UEditableTextBox* ServerIP;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UButton* SinglePlayButton;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UButton* ConnectButton;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UButton* MakeServerButton;

	UFUNCTION(BlueprintCallable)
	void PlaySingleMode();
	UFUNCTION(BlueprintCallable)
	void Connect();
	UFUNCTION(BlueprintCallable)
	void MakeServer();
	void SetUserID();

	void ConnectResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void MakeServerResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};

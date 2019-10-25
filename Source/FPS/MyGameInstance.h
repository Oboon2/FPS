// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// HTTP ���
#include "Http.h"
#include "IHttpRequest.h"
#include "IHttpResponse.h"

#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	FString UserID;
	FString GetUserID();
	
	// Post ������� �ڷ� ��û
	void HTTPPost(FString URL, FString userID, FString Password, FHttpRequestCompleteDelegate ProcessRequestComplete);


	// Get ������� �ڷ� ��û
	//void HTTPGet();

	// HTTP ��� �ݹ�
	void HTTPResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// HTTP ���
	class FHttpModule* Http;

};

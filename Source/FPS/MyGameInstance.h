// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// HTTP 모듈
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
	
	// Post 방식으로 자료 요청
	void HTTPPost(FString URL, FString userID, FString Password, FHttpRequestCompleteDelegate ProcessRequestComplete);


	// Get 방식으로 자료 요청
	//void HTTPGet();

	// HTTP 결과 콜백
	void HTTPResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// HTTP 모듈
	class FHttpModule* Http;

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Http.h"
#include "Json.h"

FString UMyGameInstance::GetUserID()
{
	if (UserID.IsEmpty())
	{
		// Lobby�� BattleMap���� �ٷν��� �Ҷ�
		UserID = FString::Printf(TEXT("Noname%d"), FMath::RandRange(0, 100));
	}
	return UserID;
}

void UMyGameInstance::HTTPPost(FString URL, FString userID, FString Password, FHttpRequestCompleteDelegate ProcessRequestComplete)
{
	// ��� ������
	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	//�ݹ� ���
	Request->OnProcessRequestComplete() = ProcessRequestComplete;

	FString PostParameters = FString::Printf(TEXT("userid=%s"), *userID)
		+ FString::Printf(TEXT("&password=%s"), *Password);
	Request->SetURL(URL);
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
	Request->SetContentAsString(PostParameters);
	Request->ProcessRequest();
}


void UMyGameInstance::HTTPResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	GLog->Log(FString::Printf(TEXT("Callback")));
	if (bWasSuccessful)
	{
		//JSON �Ľ�
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		GLog->Log(FString::Printf(TEXT("Receive %s"), *Response->GetContentAsString()));

		//if (FJsonSerializer::Deserialize(Reader, JsonObject))
		//{
		//	FString ID = JsonObject->GetStringField("id");
		//	int Password = (int)JsonObject->GetNumberField("password");

		//	GLog->Log(FString::Printf(TEXT("Parsing %s %d"), *ID, Password));
		//}
	}
}

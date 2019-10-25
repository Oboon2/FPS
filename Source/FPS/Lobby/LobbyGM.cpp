// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Lobby/LobbyGS.h"

void ALobbyGM::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(LeftTimerHandle, this, &ALobbyGM::LeftTimer, 1.0f, true, 1.0f);
}

void ALobbyGM::LeftTimer()
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS && GS->LeftTime > 0)
	{
		GS->LeftTime--;
	}
}

void ALobbyGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->ConnectCount++;
		// ���������� ����
		if (HasAuthority())
		{
			// ���������� �Լ� ������ �ȵǼ� �������� �߰�
			GS->ConnectCount_OnRep();
		}
	
	}
}

void ALobbyGM::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->ConnectCount--;
		// ���������� ����
		if (HasAuthority())
		{
			// ���������� �Լ� ������ �ȵǼ� �������� �߰�
			GS->ConnectCount_OnRep();
		}
	}
}

void ALobbyGM::GameStart()
{
	GetWorld()->ServerTravel(TEXT("Battle"));
}



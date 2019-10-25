// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGS.h"
#include "UnrealNetwork.h"
#include "Lobby/LobbyPC.h"
#include "Lobby/LobbyWidgetBase.h"
#include "Kismet/GameplayStatics.h"

ALobbyGS::ALobbyGS()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ALobbyGS::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->LobbyWidget->SetLifeTime(LeftTime);
	}
}

void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGS, LeftTime);
	DOREPLIFETIME(ALobbyGS, ConnectCount);
}

void ALobbyGS::ConnectCount_OnRep()
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->LobbyWidget)
	{
		PC->LobbyWidget->SetConnectCount(ConnectCount);
	}
}

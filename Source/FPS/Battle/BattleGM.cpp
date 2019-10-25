// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGM.h"
#include "Item/MasterItem.h"
#include "Item/ItemPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ABattleGM::ABattleGM()
{
}

void ABattleGM::BeginPlay()
{
	Super::BeginPlay();
	// 맵에서 아이템 생성 위치 가져오기
	TArray<AActor*> ItemLocations;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemPoint::StaticClass(), ItemLocations);

	// 아이템 생성
	for (auto Location : ItemLocations)
	{
		UE_LOG(LogClass, Warning, TEXT("MasterItem Make"));
		GetWorld()->SpawnActor<AMasterItem>(ItemClass, Location->GetTransform());
	}
}

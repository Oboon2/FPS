// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Item/ItemComponent.h"
#include "Engine/StreamableManager.h"
#include "Item/ItemTable.h"
#include "UnrealNetwork.h"

// Sets default values
AMasterItem::AMasterItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->SetSphereRadius(30.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Data = CreateDefaultSubobject<UItemComponent>(TEXT("Data"));

	bReplicates = true;
}

// Called when the game starts or when spawned
void AMasterItem::BeginPlay()
{
	Super::BeginPlay();

	if (Data->ItemTable)
	{
		if (HasAuthority())
		{
			ItemIndex = FMath::RandRange(1, 6) * 10;
		}
		ItemData = Data->GetItemData(ItemIndex);

		FStreamableManager Loader;
		Mesh->SetStaticMesh(Loader.LoadSynchronous<UStaticMesh>(ItemData.ItemMesh));
	}

}

void AMasterItem::LoadComplete()
{
}

// Called every frame
void AMasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMasterItem, ItemIndex);
}


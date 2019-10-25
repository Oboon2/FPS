// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemTable.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
	NotUse = 0 UMETA(Display = NotUse),
	WeaponRightHand = 1 UMETA(Display = WeaponRightHand),
	Equip = 2 UMETA(Display = Equip),
	Weapon = 3 UMETA(Display = Weapon),
};

UENUM(BlueprintType)
enum class EEquipSlot : uint8
{
	NotUse = 0 UMETA(Display = NotUse),
	WeaponRightHand = 2 UMETA(Display = WeaponRightHand),
	WeaponBack01	 = 3 UMETA(Display = WeaponBack01),
};

USTRUCT(BlueprintType)
struct FPS_API FItemTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EEquipSlot ItemEquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ItemFloat01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TAssetPtr<class UTexture2D> ItemThumnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TAssetPtr<class UStaticMesh>ItemMesh;

	
};

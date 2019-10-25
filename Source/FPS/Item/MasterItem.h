// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/ItemTable.h"
#include "MasterItem.generated.h"

UCLASS()
class FPS_API AMasterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void LoadComplete();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* Sphere;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
		class UItemComponent* Data;
	UPROPERTY(VisibleAnywhere, Replicated)
		int32 ItemIndex;
	UPROPERTY(VisibleAnywhere)
		FItemTable ItemData;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

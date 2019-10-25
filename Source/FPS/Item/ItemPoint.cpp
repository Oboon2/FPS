// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPoint.h"
#include "Components/BillboardComponent.h"
#include "ConstructorHelpers.h"

AItemPoint::AItemPoint()
{
#if WITH_EDITORONLY_DATA
	GetSpriteComponent()->RelativeScale3D = FVector(1.0f, 1.0f, 1.0f);

	static ConstructorHelpers::FObjectFinder<UTexture2D> S_Icon(TEXT("Texture2D'/Game/Items/Grenade/T_Grenade.T_Grenade'"));

	if (S_Icon.Succeeded())
	{
		GetSpriteComponent()->SetSprite(S_Icon.Object);
	}
#endif
}

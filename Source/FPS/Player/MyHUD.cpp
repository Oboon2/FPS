// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Engine/Canvas.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	FStreamableManager LoadAsset;

	FSoftObjectPath CrossHairAsset(TEXT("Texture2D'/Game/UI/crosshair.crosshair'"));
	Crosshair = Cast<UTexture2D>(LoadAsset.LoadSynchronous(CrossHairAsset));

}

void AMyHUD::DrawHUD()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	int Ruler = Canvas->SizeX / 75.0f;

	//Canvas->K2_DrawLine(FVector2D(SizeX / 2 - Ruler, SizeY / 2), FVector2D(SizeX / 2 + Ruler, SizeY / 2), 2.0f, FColor::Red);
	//Canvas->K2_DrawLine(FVector2D(SizeX / 2, SizeY / 2 - Ruler), FVector2D(SizeX / 2, SizeY / 2 + Ruler), 2.0f, FColor::Red);

	if (Crosshair)
	{
		DrawTextureSimple(Crosshair, SizeX / 2 - Crosshair->GetSizeX() / 2, SizeY / 2 - Crosshair->GetSizeY() / 2);
	}
}

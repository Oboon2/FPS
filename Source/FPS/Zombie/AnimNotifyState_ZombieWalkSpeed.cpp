// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_ZombieWalkSpeed.h"
#include "Zombie/Zombie.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAnimNotifyState_ZombieWalkSpeed::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	AZombie* Zombie = Cast<AZombie>(MeshComp->GetOwner());
	{
		if (Zombie)
		{
			Zombie->GetCharacterMovement()->MaxWalkSpeed = 1.0f;
		}
	}
}

void UAnimNotifyState_ZombieWalkSpeed::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_ZombieWalkSpeed::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	AZombie* Zombie = Cast<AZombie>(MeshComp->GetOwner());
	{
		if (Zombie)
		{
			Zombie->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
		}
	}
}

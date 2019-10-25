// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();
		bIsRunning = Pawn->bIsRunning;
		Yaw = CalculateDirection(Pawn->GetCharacterMovement()->Velocity, Pawn->GetActorRotation());

		bIsCrouched = Pawn->bIsCrouched;
		bIsIronsight = Pawn->bIsIronsight;
		bIsFalling = Pawn->GetCharacterMovement()->IsFalling();
		AimYaw = Pawn->GetAimOffset().Yaw;
		AimPitch = Pawn->GetAimOffset().Pitch;
		FireAlpha = Pawn->bIsFire ? 1 : 0;
			
	}
}

void UMyAnimInstance::AnimNotify_HelloWorld(UAnimNotify * Notify)
{
	UE_LOG(LogClass, Warning, TEXT("HelloWorld"));
}

void UMyAnimInstance::AnimNotify_MoveLock(UAnimNotify * Notify)
{
	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		Pawn->bIsMotion = true;
	}
}

void UMyAnimInstance::AnimNotify_MoveUnlock(UAnimNotify * Notify)
{
	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		Pawn->bIsMotion = false;
	}
}

void UMyAnimInstance::AnimNotify_DeadDestroy(UAnimNotify * Notify)
{
	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		Pawn->Destroy();
	}
}

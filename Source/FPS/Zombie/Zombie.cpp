// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Player/MyCharacter.h"
#include "Zombie/AI/ZombieAIController.h"
#include "GameFramework/CharacterMovementComponent.h "
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 400.0f;
	PawnSensing->SensingInterval = 0.1f;
	PawnSensing->SetPeripheralVisionAngle(45.0f);
	PawnSensing->bSeePawns = true;
	PawnSensing->bHearNoises = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	

	Tags.Add(TEXT("Zombie"));
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;

	PawnSensing->OnSeePawn.AddDynamic(this, &AZombie::OnSeenPawn);
	PawnSensing->OnHearNoise.AddDynamic(this, &AZombie::OnHeardNoise);

}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AZombie::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (CurrentHP == 0)
	{
		return 0;
	}
	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);
		if (RadialDamageEvent)
		{
			UE_LOG(LogClass, Warning, TEXT("FRadialDamageEvent %f"), DamageAmount);
		}
	}
	else if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);
		if (PointDamageEvent->HitInfo.BoneName.Compare(TEXT("Head")) == 0 || PointDamageEvent->HitInfo.BoneName.Compare(TEXT("HeadTop_End")) == 0)
		{
			CurrentHP = 0;
		}
		else
		{
			CurrentHP -= DamageAmount;
		}
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("FDamageEvevt %f"), DamageAmount);
	}

	FString HitName = FString::Printf(TEXT("Hit%d"), FMath::RandRange(1, 2));

	PlayAnimMontage(HitAnimation, 2.0f, FName(*HitName));

	CurrentHP = FMath::Clamp<float>(CurrentHP, 0, MaxHP);

	if (CurrentHP == 0)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//GetMesh()->SetSimulatePhysics(true);

		//FString DeadName = FString::Printf(TEXT("Death_%d"), FMath::RandRange(1, 3));
		//PlayAnimMontage(DeadAnimation, 1.0f, FName(*DeadName));
		CurrentState = EZombieState::Dead;
		AZombieAIController* AIC = Cast<AZombieAIController>(GetController());
		if (AIC)
		{
			AIC->SetCurrentState(CurrentState);
		}
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AZombie::OnSeenPawn(APawn * Pawn)
{
	AMyCharacter* Player = Cast<AMyCharacter>(Pawn);
	if (!Player)
	{
		return;
	}

	if (CurrentState == EZombieState::Normal && Player->ActorHasTag(TEXT("Player")) && Player->CurrentHP > 0)
	{
		CurrentState = EZombieState::Chase;
		AZombieAIController* AIC = Cast<AZombieAIController>(GetController());
		if (AIC)
		{
			AIC->SetCurrentState(CurrentState);
			AIC->SetTargetPlayer(Player);
		}
	}
	//UE_LOG(LogClass, Warning, TEXT("Seen %s"), *Pawn->GetName());
}

void AZombie::OnHeardNoise(APawn * Pawn, const FVector & Location, float Volume)
{
	//UE_LOG(LogClass, Warning, TEXT("Heard %s"), *Pawn->GetName());
}

void AZombie::Attack()
{
	AZombieAIController* AIC = Cast<AZombieAIController>(GetController());
	if (AIC)
	{
		AActor* Player = Cast<AActor>(AIC->BBComponent->GetValueAsObject(FName(TEXT("Player"))));
		if (Player)
		{
			UGameplayStatics::ApplyDamage(Player, 30.0f, GetController(), this, nullptr);
		}
	}
}




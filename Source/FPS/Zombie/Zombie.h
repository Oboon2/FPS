// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

UENUM(BlueprintType)
enum class EZombieState : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Normal = 1 UMETA(DisplayName = "Normal"),
	Chase = 2 UMETA(DisplayName = "Chase"),
	Battle = 3 UMETA(DisplayName = "Battle"),
	Dead = 4 UMETA(DisplayName = "Dead"),
};

UCLASS()
class FPS_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CurrentHP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxHP = 100.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	class UAnimMontage* DeadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EZombieState CurrentState = EZombieState::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimMontage* HitAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UBehaviorTree* ZombieAI;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UPawnSensingComponent* PawnSensing;

	UFUNCTION()
		void OnSeenPawn(APawn* Pawn);

	UFUNCTION()
		void OnHeardNoise(APawn* Pawn, const FVector& Location, float Volume);

	void Attack();

};

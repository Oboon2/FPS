// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/EngineTypes.h"
#include "MyCharacter.generated.h"

UCLASS()
class FPS_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		class UWeaponComponent* Weapon;

	UPROPERTY(BlueprintReadWrite)
		bool bIsRunning = false;

	UPROPERTY(BlueprintReadWrite, Replicated)
		bool bIsIronsight = false;

	UPROPERTY(BlueprintReadWrite)
		bool bIsMotion = false;

	UPROPERTY(BlueprintReadWrite)
		bool bIsFire = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrouchedSpeed = 150.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JogSpeed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SprintSpeed = 900.0f;


	FRotator GetAimOffset() const;

	void RunStart();
	void RunEnd();

	void Ironsight();
	void UnIronsight();
	UFUNCTION(Server, Reliable)
	void C2S_Ironsight();
	void C2S_Ironsight_Implementation();
	UFUNCTION(Server, Reliable)
	void C2S_UnIronsight();
	void C2S_UnIronsight_Implementation();
	void DoCrouch();
	void UndoCrouch();

	void StartFire();
	void StopFire();

	void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_Shot(FVector TraceStart, FVector TraceEnd);
	bool C2S_Shot_Validate(FVector TraceStart, FVector TraceEnd);
	void C2S_Shot_Implementation(FVector TraceStart, FVector TraceEnd);
	
	// Host만 사용 가능 전체 클라이언트에 전송
	UFUNCTION(NetMulticast, Reliable)
	void S2A_SpawnDecalAndEffect(FHitResult OutHit, UParticleSystem* Hit, UMaterialInterface* DecalP);
	void S2A_SpawnDecalAndEffect_Implementation(FHitResult OutHit, UParticleSystem* Hit, UMaterialInterface* DecalP);

	UFUNCTION(NetMulticast, Reliable)
	void S2A_SoundAndFlash();
	void S2A_SoundAndFlash_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void S2A_HitAnimation();
	void S2A_HitAnimation_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void S2A_DeadAnimation();
	void S2A_DeadAnimation_Implementation();

	void JumpAction();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

	FTimerHandle FireTimer;

	UFUNCTION()
		void FireTimerFunction();

	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystem* BloodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
		class USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UMaterialInterface* BulletDecal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UMaterialInterface* BloodDecal;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector NormalSpringArmPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector CrouchedSpringArmPosition;

	UFUNCTION(BlueprintCallable)
		FVector GetSpringArmPosition() const;
	UFUNCTION(BlueprintCallable)
		void SetSpringArmPosition(FVector NewPosition);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UCameraShake> FireCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
		float CurrentHP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimMontage* DeadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimMontage* HitAnimation;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	FTimerHandle LookItemHandler;

	UFUNCTION()
	void LookItem();

	void PickUp();

	FHitResult PickUpItem;

	UFUNCTION(Server, Reliable)
	void C2S_CheckPickUpItem(class AMasterItem* Item);
	void C2S_CheckPickUpItem_Implementation(class AMasterItem* Item);

	UFUNCTION(Client, Reliable)
	void S2C_CompletePickUpItem(class AMasterItem* Item);
	void S2C_CompletePickUpItem_Implementation(class AMasterItem* Item);
};

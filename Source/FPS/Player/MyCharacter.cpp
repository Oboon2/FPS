// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h "
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "WeaponComponent.h"
#include "MyCameraShake.h"
#include "UnrealNetwork.h"
#include "Item/MasterItem.h"
#include "Battle/BattlePC.h"
#include "Battle/InventoryWidgetBase.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SocketOffset = FVector(0.0f, 50.0f, 100.0f);
	SpringArm->TargetArmLength = 120.0f;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));



	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.1f;

	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchedSpeed;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	Tags.Add(TEXT("Character"));
	Tags.Add(TEXT("Player"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	NormalSpringArmPosition = SpringArm->GetRelativeTransform().GetLocation();
	CrouchedSpringArmPosition = NormalSpringArmPosition + FVector(0.0f, 0.0f, -48.0f);

	CurrentHP = MaxHP;

	GetWorldTimerManager().SetTimer(LookItemHandler, this, &AMyCharacter::LookItem, 0.1f, true);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Shift"), IE_Pressed, this, &AMyCharacter::RunStart);
	PlayerInputComponent->BindAction(TEXT("Shift"), IE_Released, this, &AMyCharacter::RunEnd);

	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Pressed, this, &AMyCharacter::Ironsight);
	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Released, this, &AMyCharacter::UnIronsight);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMyCharacter::DoCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AMyCharacter::UndoCrouch);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyCharacter::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AMyCharacter::StopFire);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyCharacter::JumpAction);

	PlayerInputComponent->BindAction(TEXT("PickUp"), IE_Pressed, this, &AMyCharacter::PickUp);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::Turn);



}

FRotator AMyCharacter::GetAimOffset() const
{
	//FVector AimDirWS = GetBaseAimRotation().Vector();
	//FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	//FRotator AimRotLS = AimDirLS.Rotation();

	//return AimRotLS;


	return ActorToWorld().InverseTransformVectorNoScale(GetBaseAimRotation().Vector()).Rotation();
}


void AMyCharacter::RunStart()
{
	bIsRunning = true;
	Cast<UCharacterMovementComponent>(GetCharacterMovement())->MaxWalkSpeed = SprintSpeed;
}

void AMyCharacter::RunEnd()
{
	bIsRunning = false;
	Cast<UCharacterMovementComponent>(GetCharacterMovement())->MaxWalkSpeed = JogSpeed;
}

void AMyCharacter::Ironsight()
{
	if (bIsMotion)
	{
		return;
	}
	bIsIronsight = true;
	GetCharacterMovement()->MaxWalkSpeed = CrouchedSpeed;
	C2S_Ironsight();
}

void AMyCharacter::UnIronsight()
{
	if (bIsMotion)
	{
		return;
	}
	bIsIronsight = false;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	C2S_UnIronsight();
}

void AMyCharacter::C2S_Ironsight_Implementation()
{
	if (bIsMotion)
	{
		return;
	}
	bIsIronsight = true;
	GetCharacterMovement()->MaxWalkSpeed = CrouchedSpeed;
}

void AMyCharacter::C2S_UnIronsight_Implementation()
{
	if (bIsMotion)
	{
		return;
	}
	bIsIronsight = false;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
}

void AMyCharacter::DoCrouch()
{
	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AMyCharacter::UndoCrouch()
{
}

void AMyCharacter::StartFire()
{
	bIsFire = true;
	Fire();
}

void AMyCharacter::StopFire()
{
	bIsFire = false;
}

void AMyCharacter::Fire()
{
	if (!bIsFire)
	{
		return;
	}

	FVector CameraLocation;
	FRotator CameraRotation;
	int32 SizeX;
	int32 SizeY;
	FVector WorldLocation;
	FVector WorldDirection;
	FVector TraceStart;
	FVector TraceEnd;
	APlayerController* PC = GetController<APlayerController>();
	if (PC)
	{
		int32 RandX = FMath::RandRange(-10, 10);
		PC->GetPlayerViewPoint(CameraLocation, CameraRotation);
		PC->GetViewportSize(SizeX, SizeY);
		PC->DeprojectScreenPositionToWorld(SizeX / 2 - RandX, SizeY / 2, WorldLocation, WorldDirection);
		TraceStart = WorldLocation;
		TraceEnd = TraceStart + (WorldDirection * 90000.0f);

		// 총 타격 판정은 서버가
		C2S_Shot(TraceStart, TraceEnd);
		

	}
	FRotator PlayerRotation = GetControlRotation();
	PlayerRotation.Pitch += FMath::RandRange(1.0f, 1.5f);
	GetController()->SetControlRotation(PlayerRotation);

	// 사운드 & 플래쉬
	void S2A_SoundAndFlash();


	// CameraShake
	if (PC)
	{
		//PC->PlayerCameraManager->PlayCameraShake(UMyCameraShake::StaticClass());
		//PC->PlayerCameraManager->PlayCameraShake();
		PC->PlayerCameraManager->PlayCameraShake(FireCameraShake);
	}


	if (bIsFire)
	{
		GetWorldTimerManager().SetTimer(FireTimer, this, &AMyCharacter::FireTimerFunction, 0.12f);
	}
}

bool AMyCharacter::C2S_Shot_Validate(FVector TraceStart, FVector TraceEnd)
{
	return true;
}

void AMyCharacter::C2S_Shot_Implementation(FVector TraceStart, FVector TraceEnd)
{
	S2A_SoundAndFlash();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	FHitResult OutHit;
	bool bResult = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, ObjectType, false, IgnoreActors, EDrawDebugTrace::None, OutHit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);

	if (bResult)
	{
		//태그로 하거나 이름받아서 하거나 선택
	   //if (OutHit.GetComponent()->GetName() == GetMesh()->GetName())
	   //{
	   //}
	   //else
	   //{
	   //}
		UParticleSystem* Hit;
		UMaterialInterface* DecalP;
		if (OutHit.GetActor()->ActorHasTag(TEXT("Character")) || OutHit.GetActor()->ActorHasTag(TEXT("Zombie")))
		{
			Hit = BloodEffect;
			DecalP = BloodDecal;
		}
		else
		{
			Hit = HitEffect;
			DecalP = BulletDecal;
		}
		
		S2A_SpawnDecalAndEffect(OutHit, Hit, DecalP);

		

		//UE_LOG(LogClass, Warning, TEXT("Hit %s"), *OutHit.GetActor()->GetName());

		TArray<AActor*> IgonoreActors;
		IgonoreActors.Add(this);


		UGameplayStatics::ApplyPointDamage(OutHit.GetActor(), 30.0f, TraceEnd - TraceStart, OutHit, GetController(), this, nullptr);


	}
}

void AMyCharacter::S2A_SpawnDecalAndEffect_Implementation(FHitResult OutHit, UParticleSystem * Hit, UMaterialInterface * DecalP)
{
	// HitEffect
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Hit, OutHit.ImpactPoint + OutHit.ImpactNormal * 5.0f, OutHit.ImpactNormal.Rotation());

	// Decal
	UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalP, FVector(5.0f, 5.0f, 5.0f), OutHit.ImpactPoint, OutHit.ImpactNormal.Rotation(), 5.0f);
	Decal->SetFadeScreenSize(0.001f);
}

void AMyCharacter::S2A_SoundAndFlash_Implementation()
{
	// Sound and MuzzleFlash
	if (FireSound && MuzzleFlash)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSound, Weapon->GetSocketLocation(TEXT("Muzzle")));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, Weapon->GetSocketTransform(TEXT("Muzzle")));
	}
}

void AMyCharacter::S2A_HitAnimation_Implementation()
{
	FString HitName = FString::Printf(TEXT("Hit%d"), FMath::RandRange(1, 4));
	PlayAnimMontage(HitAnimation, 2.0f, FName(*HitName));
}

void AMyCharacter::S2A_DeadAnimation_Implementation()
{
	FString DeadName = FString::Printf(TEXT("Death_%d"), FMath::RandRange(1, 3));
	PlayAnimMontage(DeadAnimation, 1.0f, FName(*DeadName));

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		DisableInput(PC);
	}
}

void AMyCharacter::JumpAction()
{
	Jump();
}

void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0 && !bIsMotion)
	{
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)), Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Value != 0 && !bIsMotion)
	{
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)), Value);
	}
}

void AMyCharacter::LookUp(float Value)
{
	if (Value != 0)
	{
		AddControllerPitchInput(Value);
	}
}

void AMyCharacter::Turn(float Value)
{
	if (Value != 0)
	{
		AddControllerYawInput(Value);
	}
}

void AMyCharacter::FireTimerFunction()
{
	Fire();
}

void AMyCharacter::OnBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	//if (!OtherActor->ActorHasTag(TEXT("Rocket")))
	//{
	//	if (!OtherActor->ActorHasTag(TEXT("Player"))&&)
	//	{
	//		Destroy();

	//		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
	//		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());

	//		UGameplayStatics::ApplyDamage(OtherActor, 30.0f, nullptr, this, nullptr);
	//		//OtherActor->TakeDamage(30.0f, FDamageEvent(), nullptr, this);


	//	}
	//}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
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
		if (PointDamageEvent->HitInfo.BoneName.Compare(TEXT("Head")) == 0)
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
		CurrentHP -= DamageAmount;
	}
	S2A_HitAnimation();


	CurrentHP = FMath::Clamp<float>(CurrentHP, 0, MaxHP);

	if (CurrentHP == 0)
	{
		//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//GetMesh()->SetSimulatePhysics(true);

		S2A_DeadAnimation();
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

FVector AMyCharacter::GetSpringArmPosition() const
{
	return SpringArm->GetRelativeTransform().GetLocation();
}

void AMyCharacter::SetSpringArmPosition(FVector  NewPosition)
{
	SpringArm->SetRelativeLocation(NewPosition);
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyCharacter, CurrentHP);
	DOREPLIFETIME(AMyCharacter, bIsIronsight);

}

void AMyCharacter::LookItem()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	int32 SizeX;
	int32 SizeY;
	FVector WorldLocation;
	FVector WorldDirection;
	FVector TraceStart;
	FVector TraceEnd;
	ABattlePC* PC = GetController<ABattlePC>();
	if (PC)
	{
		PC->GetPlayerViewPoint(CameraLocation, CameraRotation);
		PC->GetViewportSize(SizeX, SizeY);
		PC->DeprojectScreenPositionToWorld(SizeX / 2, SizeY / 2, WorldLocation, WorldDirection);
		TraceStart = WorldLocation;
		TraceEnd = TraceStart + (WorldDirection * 200.0f);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
		ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(this);

		FHitResult OutHit;
		bool bResult = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, ObjectType, false, IgnoreActors, EDrawDebugTrace::None, OutHit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		if (bResult)
		{
			

			AMasterItem* Item = Cast<AMasterItem>(OutHit.Actor);
			if (Item)
			{
				UE_LOG(LogClass, Warning, TEXT("%s"), *Item->ItemData.ItemName);
				PC->ShowItemName(Item->ItemData.ItemName);
				PickUpItem = OutHit;
			}
			else
			{
				PC->HideItemName();
				PickUpItem = FHitResult();
			}
		}
		else
		{
			PC->HideItemName();
			PickUpItem = FHitResult();
		}
		
	}
}

void AMyCharacter::PickUp()
{
	LookItem();
	AMasterItem* Item = Cast<AMasterItem>(PickUpItem.GetActor());
	if (Item)
	{
		C2S_CheckPickUpItem(Item);
	}
}

void AMyCharacter::C2S_CheckPickUpItem_Implementation(AMasterItem * Item)
{
	if (Item && !Item->IsPendingKill())
	{
		S2C_CompletePickUpItem(Item);
		Item->Destroy();
	}
}

void AMyCharacter::S2C_CompletePickUpItem_Implementation(AMasterItem * Item)
{
	if (Item && !Item->IsPendingKill())
	{
		ABattlePC* PC = Cast<ABattlePC>(GetController());
		if (PC)
		{
			int32 SlotIndex = PC->InventoryWidget->GetEmptySlot();
			PC->InventoryWidget->SetItemSlot(SlotIndex, Item->ItemData);
		}
	}
}

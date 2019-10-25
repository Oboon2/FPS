// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Zombie/Zombie.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AZombieAIController : public AAIController
{
	GENERATED_BODY()
public:
	AZombieAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTreeComponent* BTComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UBlackboardComponent* BBComponent;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void SetCurrentState(EZombieState NewState);

	void SetTargetPlayer(AActor* Player);

	
};

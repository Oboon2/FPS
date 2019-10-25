// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChangeSpeed.generated.h"

//UENUM(BlueprintType)
//enum class EZombieSpeed :uint8
//{
//	Walk = 0 UMETA(Display = "Walk"),
//	Run = 1 UMETA(Display = "Run"),
//};

/**
 * 
 */
UCLASS()
class FPS_API UBTTask_ChangeSpeed : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float NormalSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ChaseSpeed = 450.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	EZombieSpeed CurrentSpeed;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Zombie/Zombie.h"
#include "BTTask_CheckRange.generated.h"


UENUM(BlueprintType)
enum class ETaskCondition : uint8
{
	Less = 0 UMETA(Display = "<"),
	Greater = 1 UMETA(Display = ">"),
};
/**
 * 
 */
UCLASS()
class FPS_API UBTTask_CheckRange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETaskCondition Condition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EZombieState TargetState;

	
};

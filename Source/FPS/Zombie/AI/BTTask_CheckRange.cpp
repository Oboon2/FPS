// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckRange.h"

#include "Zombie/AI/ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie/Zombie.h"

EBTNodeResult::Type UBTTask_CheckRange::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

	if (!Player && !Zombie)
	{
		return EBTNodeResult::Failed;
	}

	float Distance = FVector::Distance(Zombie->GetActorLocation(), Player->GetActorLocation());

	switch (Condition)
	{

		case ETaskCondition::Less:
		{
			if (Distance < Range)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)TargetState);
				Zombie->CurrentState = TargetState;
			}
			break;
		}

		case ETaskCondition::Greater:
		{
			if (Distance > Range)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)TargetState);
				Zombie->CurrentState = TargetState;
			}
			break;
		}

	}

	return EBTNodeResult::Type();
}

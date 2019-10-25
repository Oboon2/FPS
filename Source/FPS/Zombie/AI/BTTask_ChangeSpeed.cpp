// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChangeSpeed.h"

#include "Zombie/AI/ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie/Zombie.h"
#include "GameFramework/CharacterMovementComponent.h "

EBTNodeResult::Type UBTTask_ChangeSpeed::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());

	if (!Zombie)
	{
		return EBTNodeResult::Failed;
	}

	//if (CurrentSpeed == EZombieSpeed::Walk)
	//{
	//	Zombie->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	//}
	//else
	//{
	//	Zombie->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	//}

	if (Zombie->CurrentState==EZombieState::Normal)
	{
		if (Zombie->GetCharacterMovement()->MaxWalkSpeed != NormalSpeed)
		{
			Zombie->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
		}
	}
	if (Zombie->CurrentState == EZombieState::Chase)
	{
		if (Zombie->GetCharacterMovement()->MaxWalkSpeed != ChaseSpeed)
		{
			Zombie->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		}
	}

	return EBTNodeResult::Succeeded;
}

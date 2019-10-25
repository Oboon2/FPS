// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckPlayerAlive.h"
#include "Zombie/Zombie.h"
#include "Zombie/AI/ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/MyCharacter.h"

void UBTService_CheckPlayerAlive::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AZombieAIController* AIC = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	if (AIC)
	{
		AMyCharacter* Player = Cast<AMyCharacter>(AIC->BBComponent->GetValueAsObject(FName(TEXT("Player"))));
		if (Player)
		{
			if (Player->CurrentHP <= 0)
			{
				AZombie* Zombie = Cast<AZombie>(AIC->GetPawn());
				if (Zombie)
				{
					Zombie->CurrentState = EZombieState::Normal;
					AIC->SetCurrentState(Zombie->CurrentState);
				}
			}
		}
	}
}

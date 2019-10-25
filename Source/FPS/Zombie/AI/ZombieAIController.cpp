// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie/Zombie.h"
#include "BehaviorTree/BehaviorTree.h"

AZombieAIController::AZombieAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
}

void AZombieAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	AZombie* Zombie = Cast<AZombie>(InPawn);
	if (Zombie && BTComponent && BBComponent)
	{
	
		BBComponent->InitializeBlackboard(*(Zombie->ZombieAI->BlackboardAsset));
		BTComponent->StartTree(*(Zombie->ZombieAI));


		//BBComponent->SetValueAsVector(FName(TEXT("Target")), FVector(100.0f, 100.0f, 0.0f));
		SetCurrentState(EZombieState::Normal);
	}
}

void AZombieAIController::OnUnPossess()
{
	BTComponent->StopTree();

	Super::OnUnPossess();
}

void AZombieAIController::SetCurrentState(EZombieState NewState)
{
	BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)NewState);
}

void AZombieAIController::SetTargetPlayer(AActor* Player)
{
	BBComponent->SetValueAsObject(FName(TEXT("Player")), Player);
}

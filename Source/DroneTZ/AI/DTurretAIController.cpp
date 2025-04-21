#include "DTurretAIController.h"
#include "DroneTZ/Characters/Enemy/DTurretEnemy.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ADTurretAIController::ADTurretAIController()
{
	// Initializing behavior tree and blackboard components
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ADTurretAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ADTurretAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ADTurretEnemy* Turret = Cast<ADTurretEnemy>(InPawn))
	{
		if (UBehaviorTree* BT = Turret->GetBehaviorTree())
		{
			if (BT->BlackboardAsset)
			{
				UE_LOG(LogTemp, Warning, TEXT("Running BT with Blackboard: %s"), *BT->BlackboardAsset->GetName());
				UseBlackboard(BT->BlackboardAsset, BlackboardComponent);
				RunBehaviorTree(BT);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("BT found, but BlackboardAsset is NULL"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No BehaviorTree found in Turret"));
		}
	}
}


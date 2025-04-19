#include "DTurretAIController.h"
#include "DroneTZ/Characters/Enemy/DTurretEnemy.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ADTurretAIController::ADTurretAIController()
{
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
		if (Turret->GetBehaviorTree())
		{
			UseBlackboard(Turret->GetBehaviorTree()->BlackboardAsset, BlackboardComponent);
			RunBehaviorTree(Turret->GetBehaviorTree());
		}
	}
}

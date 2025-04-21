#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAtTarget.generated.h"

/**
 * Behavior Tree Task that rotates the turret mesh to face the target actor.
 */
UCLASS()
class DRONETZ_API UBTTask_LookAtTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_LookAtTarget();

public:
	/** Executes the task: rotates turret toward a target actor. */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAtTarget.generated.h"

UCLASS()
class DRONETZ_API UBTTask_LookAtTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_LookAtTarget();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

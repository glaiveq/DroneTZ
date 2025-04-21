#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DTurretAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * AI Controller for Turret that manages the Behavior Tree and Blackboard components.
 * It controls how the turret reacts to the environment using behavior trees.
 */
UCLASS()
class DRONETZ_API ADTurretAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADTurretAIController();

protected:
	virtual void BeginPlay() override;

	/** Possess the turret and initialize the behavior tree. */
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComponent;
};

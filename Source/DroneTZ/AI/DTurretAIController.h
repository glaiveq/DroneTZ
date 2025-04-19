#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DTurretAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class DRONETZ_API ADTurretAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADTurretAIController();

protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComponent;
};

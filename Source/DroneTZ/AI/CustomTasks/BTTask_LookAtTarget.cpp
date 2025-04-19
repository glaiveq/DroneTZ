#include "BTTask_LookAtTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"

UBTTask_LookAtTarget::UBTTask_LookAtTarget()
{
	NodeName = "Look At Target";
}

EBTNodeResult::Type UBTTask_LookAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!Target || !ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector Direction = Target->GetActorLocation() - ControlledPawn->GetActorLocation();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewRotation.Pitch = 0.f;
	NewRotation.Roll = 0.f;

	ControlledPawn->SetActorRotation(NewRotation);

	return EBTNodeResult::Succeeded;
}

#include "BTTask_LookAtTarget.h"
#include "DroneTZ/Characters/Enemy/DTurretEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

UBTTask_LookAtTarget::UBTTask_LookAtTarget()
{
	NodeName = "Look At Target";
}

EBTNodeResult::Type UBTTask_LookAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the target actor from the blackboard
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!Target || !ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	ADTurretEnemy* Turret = Cast<ADTurretEnemy>(ControlledPawn);
	if (!Turret)
	{
		return EBTNodeResult::Failed;
	}

	// Get the mesh that should rotate
	UStaticMeshComponent* TurretMesh = Turret->GetTurretMesh();
	if (!TurretMesh)
	{
		return EBTNodeResult::Failed;
	}

	// Calculate direction and look-at rotation
	FVector Direction = Target->GetActorLocation() - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	// Apply rotation to turret
	TurretMesh->SetWorldRotation(LookAtRotation);

	return EBTNodeResult::Succeeded;
}


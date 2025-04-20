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

	UStaticMeshComponent* TurretMesh = Turret->GetTurretMesh();
	if (!TurretMesh)
	{
		return EBTNodeResult::Failed;
	}
	
	FVector Direction = Target->GetActorLocation() - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	TurretMesh->SetWorldRotation(LookAtRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Rotating turret to %s"), *LookAtRotation.ToString());

	return EBTNodeResult::Succeeded;
}


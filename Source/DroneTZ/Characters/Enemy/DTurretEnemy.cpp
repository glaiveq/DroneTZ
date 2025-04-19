#include "DTurretEnemy.h"
#include "DroneTZ/AI/DTurretAIController.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ADTurretEnemy::ADTurretEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CollisionComponent->InitCapsuleSize(42.f, 96.f);
	RootComponent = CollisionComponent;

	TurretMeshMain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMeshMain"));
	TurretMeshMain->SetupAttachment(RootComponent);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(TurretMeshMain);

	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 1200.f;
	SightConfig->LoseSightRadius = 1400.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ADTurretEnemy::OnTargetPerceived);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = ADTurretAIController::StaticClass();

	TurretMesh->SetMobility(EComponentMobility::Movable);


}

void ADTurretEnemy::BeginPlay()
{
	Super::BeginPlay();
}

UBehaviorTree* ADTurretEnemy::GetBehaviorTree() const
{
	return BehaviorTree;
}

UStaticMeshComponent* ADTurretEnemy::GetTurretMesh() const
{
	return TurretMesh;
}

void ADTurretEnemy::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Seen: %s"), *Actor->GetName());

		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent())
			{
				Blackboard->SetValueAsObject(TEXT("TargetActor"), Actor);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lost Sight of: %s"), *Actor->GetName());

		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent())
			{
				Blackboard->ClearValue(TEXT("TargetActor"));
			}
		}
	}
}

#include "DTurretEnemy.h"
#include "DroneTZ/AI/DTurretAIController.h"
#include "DroneTZ/ShootingSystem/DProjectileShooterComponent.h"
#include "DroneTZ/Health/DHealthComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"

ADTurretEnemy::ADTurretEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CollisionComponent->InitCapsuleSize(42.f, 96.f);
	RootComponent = CollisionComponent;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(RootComponent);
	
	TurretMeshMain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMeshMain"));
	TurretMeshMain->SetupAttachment(RootComponent);

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	TurretMeshMain->SetupAttachment(RootComponent);
	
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

	HealthComponent = CreateDefaultSubobject<UDHealthComponent>("HealthComponent");

	ProjectileShooter = CreateDefaultSubobject<UDProjectileShooterComponent>(TEXT("ProjectileShooter"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = ADTurretAIController::StaticClass();

	TurretMesh->SetMobility(EComponentMobility::Movable);
}

void ADTurretEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &ADTurretEnemy::OnTurretHealthChanged);
		HealthComponent->OnDeath.AddDynamic(this, &ADTurretEnemy::OnTurretDeath);
	}
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
		
		GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &ADTurretEnemy::TryShootAtTarget, 0.2f, true);
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
		
		GetWorldTimerManager().ClearTimer(ShootingTimerHandle);
	}
}

void ADTurretEnemy::TryShootAtTarget()
{
	if (!ProjectileShooter)
	{
		return;
	}

	AActor* Target = nullptr;

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent())
		{
			Target = Cast<AActor>(Blackboard->GetValueAsObject(TEXT("TargetActor")));
		}
	}

	if (Target)
	{
		ProjectileShooter->ShootProjectile();
	}
}

void ADTurretEnemy::OnTurretHealthChanged(float NewHealth, float Delta)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret Health: %f"), NewHealth);
}

void ADTurretEnemy::OnTurretDeath()
{
	UE_LOG(LogTemp, Error, TEXT("Turret Died"));
	Destroy();
}

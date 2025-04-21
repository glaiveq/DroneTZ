#include "DTurretEnemy.h"
#include "DroneTZ/AI/DTurretAIController.h"
#include "DroneTZ/ShootingSystem/DProjectileShooterComponent.h"
#include "DroneTZ/Health/DHealthComponent.h"
#include "DroneTZ/UI/DTurretHealthWidget.h"
#include "DroneTZ/Characters/DBaseDrone.h"

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

	// Initializing the capsule component (used for collision detection)
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CollisionComponent->InitCapsuleSize(42.f, 96.f);
	RootComponent = CollisionComponent;

	// Setting up the turret mesh components
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(RootComponent);
	
	TurretMeshMain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMeshMain"));
	TurretMeshMain->SetupAttachment(RootComponent);

	// Creating and attaching a health bar widget to the turret
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetRelativeRotation(FRotator::ZeroRotator);
	HealthBarWidget->SetupAttachment(TurretMeshMain);

	// Initializing the AI perception and sight configurations for detecting targets
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	// Setting the perception parameters: sight range, peripheral vision, etc.
	SightConfig->SightRadius = 1200.f;
	SightConfig->LoseSightRadius = 1400.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// Configuring the perception component with the sight configuration
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	// Binding the perception update event to handle target detection
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ADTurretEnemy::OnTargetPerceived);

	// Initializing health and shooting components
	HealthComponent = CreateDefaultSubobject<UDHealthComponent>("HealthComponent");
	ProjectileShooter = CreateDefaultSubobject<UDProjectileShooterComponent>(TEXT("ProjectileShooter"));

	// Assigning AI controller and enabling auto possession
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ADTurretAIController::StaticClass();
	
	TurretMesh->SetMobility(EComponentMobility::Movable);
}

void ADTurretEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Binding health and death events to the turret's health system
	HealthComponent->OnHealthChanged.AddDynamic(this, &ADTurretEnemy::OnTurretHealthChanged);
	HealthComponent->OnDeath.AddDynamic(this, &ADTurretEnemy::OnTurretDeath);

	// Start a timer to update the health bar rotation to face the player, avoiding ticks
	GetWorld()->GetTimerManager().SetTimer(FacePlayerTimerHandle, this, &ADTurretEnemy::UpdateWidgetRotation, 0.1f, true);
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
		// Log when a target is successfully sensed
		UE_LOG(LogTemp, Warning, TEXT("Target Seen: %s"), *Actor->GetName());

		// Update the AI controller's blackboard with the new target
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent())
			{
				Blackboard->SetValueAsObject(TEXT("TargetActor"), Actor);
			}
		}

		// Start the shooting timer once the target is perceived, avoiding ticks
		GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &ADTurretEnemy::TryShootAtTarget, 0.2f, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lost Sight of: %s"), *Actor->GetName());

		// Clear the target from the AI controller's blackboard when the target is lost
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent())
			{
				Blackboard->ClearValue(TEXT("TargetActor"));
			}
		}

		// Stop the shooting timer when the target is lost
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

	// If the target is invalid or dead, do not shoot
	if (!Target || !Target->IsValidLowLevel())
		return;

	ADBaseDrone* Drone = Cast<ADBaseDrone>(Target);
	if (Drone && Drone->IsDead())
		return;

	// If a valid target is present, shoot a projectile
	if (Target)
	{
		ProjectileShooter->ShootProjectile();
	}
}

void ADTurretEnemy::UpdateWidgetRotation()
{
	// Get the player controller and player pawn to face the health widget toward the player
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	APawn* PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn) return;

	// Calculate the direction to the player and set the widget's rotation
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector WidgetLocation = HealthBarWidget->GetComponentLocation();

	FVector Direction = PlayerLocation - WidgetLocation;
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	// Prevent the widget from tilting up or down
	LookAtRotation.Pitch = 0.f;
	LookAtRotation.Roll = 0.f;

	HealthBarWidget->SetWorldRotation(LookAtRotation);
}

void ADTurretEnemy::OnTurretHealthChanged(float NewHealth, float Delta)
{
	// Update the health bar widget when the turret's health changes
	UE_LOG(LogTemp, Warning, TEXT("Turret Health: %f"), NewHealth);

	if (HealthBarWidget)
	{
		UDTurretHealthWidget* HealthWidget = Cast<UDTurretHealthWidget>(HealthBarWidget->GetUserWidgetObject());
		if (HealthWidget)
		{
			const float MaxHealth = HealthComponent->GetMaxHealth();
			HealthWidget->UpdateTurretHealth(NewHealth, MaxHealth);
		}
	}
}

void ADTurretEnemy::OnTurretDeath()
{
	// Log and destroy the turret when it dies
	UE_LOG(LogTemp, Error, TEXT("Turret Died"));
	Destroy();
}

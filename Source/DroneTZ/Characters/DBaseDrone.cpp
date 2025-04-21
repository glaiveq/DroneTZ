#include "DBaseDrone.h"
#include "DroneTZ/Health/DHealthComponent.h"
#include "DroneTZ/UI/HUD/DDroneHUD.h"
#include "DroneTZ/Camera/DDroneHitCameraShake.h"
#include "DroneTZ/Audio/DAudioComponent.h"

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

ADBaseDrone::ADBaseDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	// Collision setup
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("CollisionComponent");
	CollisionComponent->InitCapsuleSize(34.f, 88.f);
	CollisionComponent->SetCollisionProfileName("Pawn");
	CollisionComponent->SetEnableGravity(false);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SetRootComponent(CollisionComponent);

	// Skeletal Mesh setup
	DroneMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MainMesh");
	DroneMesh->SetupAttachment(CollisionComponent);
	DroneMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	DroneMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	DroneMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DroneMesh->SetSimulatePhysics(false);

	// SpringArm setup for camera positioning
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(DroneMesh, TEXT("camera_jnt_56"));
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 3.7f));
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bUsePawnControlRotation = true;

	// Camera setup
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Camera->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	Camera->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Floating movement logic
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = CollisionComponent;

	// Health system
	HealthComponent = CreateDefaultSubobject<UDHealthComponent>("HealthComponent");

	// Audio (engine hum, SFX, etc.)
	AudioComponent = CreateDefaultSubobject<UDAudioComponent>(TEXT("AudioComponent"));
	
	// Drone stats
	MaxAmmo = 10;
	CurrentAmmo = MaxAmmo;

}

void ADBaseDrone::BeginPlay()
{
	Super::BeginPlay();

	// Bind health change and death delegates
	HealthComponent->OnHealthChanged.AddDynamic(this, &ADBaseDrone::OnHealthChanged);
	HealthComponent->OnDeath.AddDynamic(this, &ADBaseDrone::OnDeath);
	
	// Update HUD with starting health
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ADDroneHUD* HUD = Cast<ADDroneHUD>(PC->GetHUD()))
		{
			HUD->UpdateHealthDisplay(HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());
		}
	}
	
	// Play initial drone sound
	AudioComponent->PlayDroneSound();

}

void ADBaseDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADBaseDrone::OnHealthChanged(float NewHealth, float Delta)
{
	UE_LOG(LogTemp, Warning, TEXT("Drone Health: %f"), NewHealth);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ADDroneHUD* HUD = Cast<ADDroneHUD>(PC->GetHUD()))
		{
			HUD->UpdateHealthDisplay(NewHealth, HealthComponent->GetMaxHealth());
		}

		// React to damage with feedback
		if (Delta < 0.f)
		{
			PC->PlayerCameraManager->StartCameraShake(UDDroneHitCameraShake::StaticClass());

			if (AudioComponent)
			{
				AudioComponent->PlayHitSound();
			}
		}
	}
}

void ADBaseDrone::OnDeath()
{
	UE_LOG(LogTemp, Error, TEXT("Drone Died"));

	// Prevent further input
	DisableInput(nullptr);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->PlayerCameraManager->StartCameraShake(UDDroneHitCameraShake::StaticClass());

		if (ADDroneHUD* HUD = Cast<ADDroneHUD>(PC->GetHUD()))
		{
			HUD->PlayBlackScreenFade();
		}
	}

	// Enable ragdoll-like physics reaction
	CollisionComponent->SetEnableGravity(true);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->AddImpulse(FVector(FMath::FRandRange(-1.f,1.f), FMath::FRandRange(-1.f,1.f), -1.f) * 300.f);

	AudioComponent->StopDroneSound();

	// Delay before respawn or level reload
	GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, this, &ADBaseDrone::HandleDeath, 4.0f, false);
}

bool ADBaseDrone::IsDead()
{
	return HealthComponent->GetCurrentHealth() <= 0.f;
}

void ADBaseDrone::HandleDeath()
{
	UGameplayStatics::OpenLevel(this, FName("L_MainTestMap"));
}


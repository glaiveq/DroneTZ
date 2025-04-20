#include "DBaseDrone.h"
#include "DroneTZ/Health/DHealthComponent.h"
#include "DroneTZ/UI/HUD/DDroneHUD.h"
#include "DroneTZ/Camera/DDroneHitCameraShake.h"
#include "DroneTZ/Audio/DAudioComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ADBaseDrone::ADBaseDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("CollisionComponent");
	CollisionComponent->InitCapsuleSize(34.f, 88.f);
	CollisionComponent->SetCollisionProfileName("Pawn");
	CollisionComponent->SetEnableGravity(false);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);

	SetRootComponent(CollisionComponent);
	
	DroneMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MainMesh");
	DroneMesh->SetupAttachment(CollisionComponent);
	DroneMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	DroneMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	DroneMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DroneMesh->SetSimulatePhysics(false);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(DroneMesh, TEXT("camera_jnt_56"));
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 3.7f));
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Camera->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	Camera->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(DroneMesh);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = CollisionComponent;

	HealthComponent = CreateDefaultSubobject<UDHealthComponent>("HealthComponent");

	AudioComponent = CreateDefaultSubobject<UDAudioComponent>(TEXT("AudioComponent"));
	
	// Setting some stats
	MaxAmmo = 10.f;
	MaxHealth = 100.f;
	
	CurrentHealth = MaxHealth;
	CurrentAmmo = MaxAmmo;

}

void ADBaseDrone::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &ADBaseDrone::OnHealthChanged);
		HealthComponent->OnDeath.AddDynamic(this, &ADBaseDrone::OnDeath);
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ADDroneHUD* HUD = Cast<ADDroneHUD>(PC->GetHUD()))
		{
			HUD->UpdateHealthDisplay(CurrentHealth, MaxHealth);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Drone spawned at location: %s"), *GetActorLocation().ToString());

}

void ADBaseDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
			HUD->UpdateHealthDisplay(NewHealth, MaxHealth);
		}
		
		if (Delta < 0.f && PC->PlayerCameraManager)
		{
			PC->PlayerCameraManager->StartCameraShake(UDDroneHitCameraShake::StaticClass());
		}

		if (AudioComponent)
		{
			AudioComponent->PlayHitSound();
		}
	}
}


void ADBaseDrone::OnDeath()
{
	UE_LOG(LogTemp, Error, TEXT("Drone Died"));
}


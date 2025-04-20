#include "DBaseDrone.h"
#include "DroneTZ/Health/DHealthComponent.h"
#include "DroneTZ/UI/HUD/DDroneHUD.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ADBaseDrone::ADBaseDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("RootSceneComponent");
	SetRootComponent(RootSceneComponent);
	
	DroneMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MainMesh");
	DroneMesh->SetupAttachment(RootSceneComponent);
	DroneMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	DroneMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	DroneMesh->SetEnableGravity(false);
	DroneMesh->SetSimulatePhysics(true);

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
	MovementComponent->UpdatedComponent = RootComponent;

	HealthComponent = CreateDefaultSubobject<UDHealthComponent>("HealthComponent");
	
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

	OnHealthChanged(CurrentHealth, MaxHealth);
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
	}
}


void ADBaseDrone::OnDeath()
{
	UE_LOG(LogTemp, Error, TEXT("Drone Died"));
}


#include "DBaseDrone.h"

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
	
	// Setting some stats
	MaxAmmo = 10.f;

	MaxHealth = 100.f;
	
	CurrentHealth = MaxHealth;
	CurrentAmmo = MaxAmmo;

}

void ADBaseDrone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADBaseDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADBaseDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


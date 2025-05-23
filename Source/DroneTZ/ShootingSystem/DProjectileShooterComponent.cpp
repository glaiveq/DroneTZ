#include "DProjectileShooterComponent.h"
#include "DroneTZ/Audio/DAudioComponent.h"

#include "Actors/DProjectile.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"


UDProjectileShooterComponent::UDProjectileShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // Disable ticking
	
	// Initialize variables
	ProjectileSpeed = 2000.f;
	MuzzleSocketName = "Muzzle";
	FireCooldown = 0.2f;
	MaxAmmo = 10;
	CurrentAmmo = 10;
	LastFireTime = -999.f;
}

void UDProjectileShooterComponent::BeginPlay()
{
	Super::BeginPlay();

	// Reset ammo when gameplay begins
	CurrentAmmo = MaxAmmo;
	
}

bool UDProjectileShooterComponent::ShootProjectile()
{
	// Check if the projectile class is valid and ammo is available
	if (!ProjectileClass || CurrentAmmo <= 0)
	{
		OnShootEmpty.Broadcast();
		return false;
	}

	// Check if the cooldown has elapsed
	const float Time = GetWorld()->GetTimeSeconds();
	if (Time - LastFireTime < FireCooldown)
	{
		return false;
	}

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return false;
	}

	// Calculate spawn location and rotation
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FVector ShootDirection = FVector::ForwardVector;

	bool bUsedCameraView = false;

	// Determine spawn position and rotation based on camera view (for player)
	if (APawn* OwnerPawn = Cast<APawn>(Owner))
	{
		APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
		if (PC)
		{
			FVector CameraLocation;
			FRotator CameraRotation;
			PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

			ShootDirection = CameraRotation.Vector();
			SpawnRotation = CameraRotation;
			bUsedCameraView = true;

			// Use muzzle socket location if available
			if (USkeletalMeshComponent* Mesh = Owner->FindComponentByClass<USkeletalMeshComponent>())
			{
				if (Mesh->DoesSocketExist(MuzzleSocketName))
				{
					SpawnLocation = Mesh->GetSocketLocation(MuzzleSocketName);
				}
				else
				{
					SpawnLocation = Mesh->GetComponentLocation();
				}
			}
			else
			{
				SpawnLocation = Owner->GetActorLocation();
			}
		}
	}

	// Fallback if camera view is not used
	if (!bUsedCameraView)
	{
		USceneComponent* MuzzleComponent = nullptr;

		// Determine muzzle location using available mesh components
		if (USkeletalMeshComponent* Skeletal = Owner->FindComponentByClass<USkeletalMeshComponent>())
		{
			if (Skeletal->DoesSocketExist(MuzzleSocketName))
			{
				MuzzleComponent = Skeletal;
			}
		}
		else if (UStaticMeshComponent* Static = Owner->FindComponentByClass<UStaticMeshComponent>())
		{
			if (Static->DoesSocketExist(MuzzleSocketName))
			{
				MuzzleComponent = Static;
			}
		}

		if (MuzzleComponent)
		{
			SpawnLocation = MuzzleComponent->GetSocketLocation(MuzzleSocketName);
			SpawnRotation = MuzzleComponent->GetSocketRotation(MuzzleSocketName);
			ShootDirection = SpawnRotation.Vector();
		}
		else
		{
			SpawnLocation = Owner->GetActorLocation();
			SpawnRotation = Owner->GetActorRotation();
			ShootDirection = SpawnRotation.Vector();
		}
	}

	// Spawn the projectile
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.Instigator = Cast<APawn>(Owner);

	ADProjectile* Projectile = GetWorld()->SpawnActor<ADProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (!Projectile)
	{
		Projectile->OwnerActor = Owner;
		return false;
	}

	Projectile->OwnerActor = Owner;

	// Ignore the owner actor when moving the projectile
	if (UPrimitiveComponent* ProjectileCollision = Projectile->FindComponentByClass<UPrimitiveComponent>())
	{
		ProjectileCollision->IgnoreActorWhenMoving(Owner, true);
	}

	// Set projectile movement
	if (UProjectileMovementComponent* Movement = Projectile->FindComponentByClass<UProjectileMovementComponent>())
	{
		Movement->Velocity = ShootDirection * ProjectileSpeed;
	}

	// Decrease ammo and update last fire time
	CurrentAmmo--;
	LastFireTime = Time;

	// UE_LOG(LogTemp, Warning, TEXT("Ammo: %d"), CurrentAmmo);

	return true;
}

void UDProjectileShooterComponent::AddAmmo(int32 Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo); // Ensure ammo is within valid range
}

int32 UDProjectileShooterComponent::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

int32 UDProjectileShooterComponent::GetMaxAmmo() const
{
	return MaxAmmo;
}


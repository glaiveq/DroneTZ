#include "DProjectileShooterComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"


UDProjectileShooterComponent::UDProjectileShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	// Setting some vrbls
	ProjectileSpeed = 2000.f;
	MuzzleSocketName = "Muzzle";
	FireCooldown = 0.2f;
	int32 MaxAmmo = 10;
	int32 CurrentAmmo = 0;
	float LastFireTime = -999.f;
}

void UDProjectileShooterComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
	
}

void UDProjectileShooterComponent::ShootProjectile()
{
	if (!ProjectileClass || CurrentAmmo <= 0)
	{
		return;
	}

	const float Time = GetWorld()->GetTimeSeconds();
	if (Time - LastFireTime < FireCooldown)
	{
		return;
	}

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	FTransform SpawnTransform;

	if (USkeletalMeshComponent* Mesh = Owner->FindComponentByClass<USkeletalMeshComponent>())
	{
		if (Mesh->DoesSocketExist(MuzzleSocketName))
		{
			SpawnTransform = Mesh->GetSocketTransform(MuzzleSocketName);
		}
		else
		{
			SpawnTransform = Mesh->GetComponentTransform();
		}
	}
	else
	{
		SpawnTransform = Owner->GetActorTransform();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.Instigator = Cast<APawn>(Owner);

	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), SpawnParams);

	if (Projectile)
	{
		if (UProjectileMovementComponent* Movement = Projectile->FindComponentByClass<UProjectileMovementComponent>())
		{
			Movement->Velocity = SpawnTransform.GetRotation().Vector() * ProjectileSpeed;
		}
	}

	CurrentAmmo--;
	LastFireTime = Time;
}

void UDProjectileShooterComponent::AddAmmo(int32 Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);
}

int32 UDProjectileShooterComponent::GetCurrentAmmo() const
{
	return CurrentAmmo;
}


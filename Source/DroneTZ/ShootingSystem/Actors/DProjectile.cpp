#include "DProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ADProjectile::ADProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(15.f);
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &ADProjectile::OnProjectileHit);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(CollisionComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	InitialLifeSpan = LifeTime;
	
	// Setting some variables
	Damage = 20.f;
	LifeTime = 3.f;

}

void ADProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, FVector NormalImpulse,
								   const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, nullptr);
	}

	Destroy();
}


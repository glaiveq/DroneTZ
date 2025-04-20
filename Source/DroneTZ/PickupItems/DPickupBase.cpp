#include "DPickupBase.h"
#include "DroneTZ/Characters/Player/DDronePawn.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


ADPickupBase::ADPickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(100.f);
	CollisionSphere->SetCollisionProfileName("OverlapAllDynamic");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void ADPickupBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADPickupBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (ADDronePawn* DronePawn = Cast<ADDronePawn>(OtherActor))
	{
		ApplyPickup(DronePawn);
		Destroy();
	}
}

void ADPickupBase::ApplyPickup(ADDronePawn* DronePawn)
{
}



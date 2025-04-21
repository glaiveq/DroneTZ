#include "DPickupBase.h"
#include "DroneTZ/Characters/Player/DDronePawn.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


ADPickupBase::ADPickupBase()
{
	PrimaryActorTick.bCanEverTick = false; // No need for tick updates

	// Set up the collision sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(100.f);
	CollisionSphere->SetCollisionProfileName("OverlapAllDynamic");

	// Set up the static mesh component
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

	// Check if the overlapping actor is a DronePawn
	if (ADDronePawn* DronePawn = Cast<ADDronePawn>(OtherActor))
	{
		ApplyPickup(DronePawn);
		Destroy();
	}
}

void ADPickupBase::ApplyPickup(ADDronePawn* DronePawn)
{
	// This function will be implemented by child classes
	
}



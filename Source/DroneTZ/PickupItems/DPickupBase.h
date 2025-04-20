#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DPickupBase.generated.h"

class ADDronePawn;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DRONETZ_API ADPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADPickupBase();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	virtual void ApplyPickup(ADDronePawn* DronePawn);
	
protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

};

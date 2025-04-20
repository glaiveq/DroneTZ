#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class DRONETZ_API ADProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ADProjectile();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
						 UPrimitiveComponent* OtherComp, FVector NormalImpulse,
						 const FHitResult& Hit);

	UFUNCTION()
	void NotifyHit(UPrimitiveComponent* MyComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
	FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float LifeTime;

};

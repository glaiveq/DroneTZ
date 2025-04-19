#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DProjectileShooterComponent.generated.h"

class ADProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONETZ_API UDProjectileShooterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDProjectileShooterComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void ShootProjectile();
	
	void AddAmmo(int32 Amount);
	
	int32 GetCurrentAmmo() const;

	int32 GetMaxAmmo() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ADProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireCooldown;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	int32 MaxAmmo;

	int32 CurrentAmmo;
	
	float LastFireTime;
};

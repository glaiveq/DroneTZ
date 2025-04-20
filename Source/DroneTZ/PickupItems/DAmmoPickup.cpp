#include "DAmmoPickup.h"
#include "DroneTZ/Characters/Player/DDronePawn.h"
#include "DroneTZ/ShootingSystem/DProjectileShooterComponent.h"

ADAmmoPickup::ADAmmoPickup()
{
	AmmoAmount = 5;
}

void ADAmmoPickup::ApplyPickup(ADDronePawn* DronePawn)
{
	Super::ApplyPickup(DronePawn);

	if (DronePawn && DronePawn->GetShooterComponent())
	{
		DronePawn->GetShooterComponent()->AddAmmo(AmmoAmount);
	}
}

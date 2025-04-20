#include "DHealthPickup.h"
#include "DroneTZ/Characters/Player/DDronePawn.h"

ADHealthPickup::ADHealthPickup()
{
	HealAmount = 25.f;
}

void ADHealthPickup::ApplyPickup(ADDronePawn* DronePawn)
{
	Super::ApplyPickup(DronePawn);
	
	if (DronePawn)
	{
		DronePawn->AddHealth(HealAmount);
	}
}

#pragma once

#include "CoreMinimal.h"
#include "DPickupBase.h"
#include "DAmmoPickup.generated.h"

UCLASS()
class DRONETZ_API ADAmmoPickup : public ADPickupBase
{
	GENERATED_BODY()

public:
	ADAmmoPickup();
	
public:
	virtual void ApplyPickup(ADDronePawn* DronePawn) override;

protected:
	UPROPERTY(EditAnywhere)
	int32 AmmoAmount;
	
};

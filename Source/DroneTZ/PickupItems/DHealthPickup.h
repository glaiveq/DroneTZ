#pragma once

#include "CoreMinimal.h"
#include "DPickupBase.h"
#include "DHealthPickup.generated.h"

UCLASS()
class DRONETZ_API ADHealthPickup : public ADPickupBase
{
	GENERATED_BODY()

public:
	ADHealthPickup();
	
public:
	virtual void ApplyPickup(ADDronePawn* DronePawn) override;

protected:
	UPROPERTY(EditAnywhere)
	float HealAmount;
};

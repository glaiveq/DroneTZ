#pragma once

#include "CoreMinimal.h"
#include "Shakes/LegacyCameraShake.h"
#include "DDroneShootCameraShake.generated.h"

UCLASS()
class DRONETZ_API UDDroneShootCameraShake : public ULegacyCameraShake
{
	GENERATED_BODY()
	
public:
	UDDroneShootCameraShake();
};

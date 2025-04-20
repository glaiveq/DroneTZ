#pragma once

#include "CoreMinimal.h"
#include "Shakes/LegacyCameraShake.h"
#include "DDroneHitCameraShake.generated.h"

UCLASS()
class DRONETZ_API UDDroneHitCameraShake : public ULegacyCameraShake
{
	GENERATED_BODY()

public:
	UDDroneHitCameraShake();
	
};

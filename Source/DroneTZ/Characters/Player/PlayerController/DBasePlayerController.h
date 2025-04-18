#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DBasePlayerController.generated.h"

UCLASS()
class DRONETZ_API ADBasePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};

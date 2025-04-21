#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DDroneHUD.generated.h"

class UDDroneHUDWidget;

UCLASS()
class DRONETZ_API ADDroneHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void UpdateAmmoDisplay(int32 Current, int32 Max);
	
	void UpdateHealthDisplay(float Current, float Max);

	void PlayBlackScreenFade();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDDroneHUDWidget> DroneWidgetClass;

	UPROPERTY()
	UDDroneHUDWidget* DroneWidget;
};

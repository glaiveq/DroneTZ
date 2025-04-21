#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DDroneHUDWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UWidgetAnimation;

UCLASS()
class DRONETZ_API UDDroneHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDDroneHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	// Function to update the ammo display on the HUD
	UFUNCTION(BlueprintCallable)
	void UpdateAmmo(int32 Current, int32 Max);

	// Function to update the health bar on the HUD
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float Current, float Max);

	// Function to just play the death screen animation
	void PlayDeathAnimation();

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AmmoText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* BlackScreenFade;
};

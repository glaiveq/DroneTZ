#include "DDroneHUD.h"

#include "DroneTZ/UI/DDroneHUDWidget.h"

void ADDroneHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create and add the HUD widget to the viewport
	if (DroneWidgetClass)
	{
		DroneWidget = CreateWidget<UDDroneHUDWidget>(GetWorld(), DroneWidgetClass);
		if (DroneWidget)
		{
			DroneWidget->AddToViewport();
		}
	}
}

void ADDroneHUD::UpdateAmmoDisplay(int32 Current, int32 Max)
{
	// Update the ammo display in the widget
	if (DroneWidget)
	{
		DroneWidget->UpdateAmmo(Current, Max);
	}
}

void ADDroneHUD::UpdateHealthDisplay(float Current, float Max)
{
	// Update the health display in the widget
	if (DroneWidget)
	{
		DroneWidget->UpdateHealth(Current, Max);
	}
}

void ADDroneHUD::PlayBlackScreenFade()
{
	// Trigger the death animation on the widget
	if (DroneWidget)
	{
		DroneWidget->PlayDeathAnimation();
	}
}

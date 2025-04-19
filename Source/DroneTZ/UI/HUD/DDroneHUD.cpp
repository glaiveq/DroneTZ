#include "DDroneHUD.h"

#include "DroneTZ/UI/DDroneHUDWidget.h"

void ADDroneHUD::BeginPlay()
{
	Super::BeginPlay();

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
	if (DroneWidget)
	{
		DroneWidget->UpdateAmmo(Current, Max);
	}
}

#include "DDroneHUDWidget.h"

#include "Components/TextBlock.h"

UDDroneHUDWidget::UDDroneHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDDroneHUDWidget::UpdateAmmo(int32 Current, int32 Max)
{
	if (AmmoText)
	{
		AmmoText->SetText(FText::FromString(FString::Printf(TEXT("Ammo: %d | %d"), Current, Max)));
	}
}

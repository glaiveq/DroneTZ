#include "DDroneHUDWidget.h"

#include "Components/ProgressBar.h"
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

void UDDroneHUDWidget::UpdateHealth(float Current, float Max)
{
	if (HealthBar && Max > 0.f)
	{
		float Percent = FMath::Clamp(Current / Max, 0.f, 1.f);
		HealthBar->SetPercent(Percent);
	}
}

void UDDroneHUDWidget::PlayDeathAnimation()
{
	PlayAnimation(BlackScreenFade);
}

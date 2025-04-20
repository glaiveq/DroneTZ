#include "DTurretHealthWidget.h"

#include "Components/ProgressBar.h"

UDTurretHealthWidget::UDTurretHealthWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDTurretHealthWidget::UpdateTurretHealth(float Current, float Max)
{
	if (TurretHealthBar && Max > 0.f)
	{
		float Percent = FMath::Clamp(Current / Max, 0.f, 1.f);
		TurretHealthBar->SetPercent(Percent);
	}
}

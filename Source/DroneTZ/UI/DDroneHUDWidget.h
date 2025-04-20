#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DDroneHUDWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class DRONETZ_API UDDroneHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDDroneHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAmmo(int32 Current, int32 Max);

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float Current, float Max);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AmmoText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
};

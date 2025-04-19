#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DDroneHUDWidget.generated.h"

UCLASS()
class DRONETZ_API UDDroneHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDDroneHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAmmo(int32 Current, int32 Max);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoText;
};

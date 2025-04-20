#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DTurretHealthWidget.generated.h"

class UProgressBar;

UCLASS()
class DRONETZ_API UDTurretHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UDTurretHealthWidget(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
	void UpdateTurretHealth(float Current, float Max);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* TurretHealthBar;
	
};

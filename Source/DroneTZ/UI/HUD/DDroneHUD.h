#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DDroneHUD.generated.h"


UCLASS()
class DRONETZ_API ADDroneHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> DroneWidgetClass;

	UPROPERTY()
	UUserWidget* DroneWidget;
};

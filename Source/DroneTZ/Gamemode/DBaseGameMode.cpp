#include "DBaseGameMode.h"
#include "DroneTZ/UI/HUD/DDroneHUD.h"

ADBaseGameMode::ADBaseGameMode()
{
	HUDClass = ADDroneHUD::StaticClass();
}

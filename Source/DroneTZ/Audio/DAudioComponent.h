#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DAudioComponent.generated.h"

class USoundBase;
class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONETZ_API UDAudioComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDAudioComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayShootSound();
	
	void PlayHitSound();

	void PlayEmptyClipSound();

	void PlayDroneSound();

	void StopDroneSound();

private:
	void PlaySound(USoundBase* Sound);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* ShootSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* EmptyClipSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* DroneSound;

	UPROPERTY()
	UAudioComponent* DroneAudioComponent;
};

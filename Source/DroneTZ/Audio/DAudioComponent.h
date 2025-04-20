// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DAudioComponent.generated.h"

class USoundBase;

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
	
	void PlayDeathSound();

	void PlayEmptyClipSound();

private:
	void PlaySound(USoundBase* Sound);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* ShootSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* EmptyClipSound;
};

#include "DAudioComponent.h"

#include "Kismet/GameplayStatics.h"

UDAudioComponent::UDAudioComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UDAudioComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UDAudioComponent::PlayShootSound()
{
	PlaySound(ShootSound);
}

void UDAudioComponent::PlayHitSound()
{
	PlaySound(HitSound);
}

void UDAudioComponent::PlayDeathSound()
{
}

void UDAudioComponent::PlayEmptyClipSound()
{
	PlaySound(EmptyClipSound);
}

void UDAudioComponent::PlaySound(USoundBase* Sound)
{
	if (Sound && GetOwner())
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetOwner()->GetActorLocation());
	}
}

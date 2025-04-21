#include "DAudioComponent.h"
#include "Components/AudioComponent.h"
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

void UDAudioComponent::PlayDroneSound()
{
	if (!DroneSound || !GetOwner()) return;

	if (!DroneAudioComponent)
	{
		DroneAudioComponent = NewObject<UAudioComponent>(GetOwner());
		if (DroneAudioComponent)
		{
			DroneAudioComponent->bAutoActivate = false;
			DroneAudioComponent->RegisterComponent();
			DroneAudioComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
	}

	if (DroneAudioComponent && !DroneAudioComponent->IsPlaying())
	{
		DroneAudioComponent->SetSound(DroneSound);
		DroneAudioComponent->Play();
	}
}

void UDAudioComponent::StopDroneSound()
{
	if (DroneAudioComponent && DroneAudioComponent->IsPlaying())
	{
		DroneAudioComponent->Stop();
	}
}

void UDAudioComponent::PlaySound(USoundBase* Sound)
{
	if (Sound && GetOwner())
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetOwner()->GetActorLocation());
	}
}

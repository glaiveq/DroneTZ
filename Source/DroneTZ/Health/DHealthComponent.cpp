#include "DHealthComponent.h"

UDHealthComponent::UDHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Setting variables
	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
}

void UDHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UDHealthComponent::TakeDamage(float DamageAmount)
{
	if (DamageAmount <= 0.f || CurrentHealth <= 0.f)
		return;

	const float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth, CurrentHealth - OldHealth);

	if (CurrentHealth <= 0.f)
	{
		OnDeath.Broadcast();
	}
}

void UDHealthComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0.f || CurrentHealth <= 0.f)
		return;

	const float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth, CurrentHealth - OldHealth);
}

float UDHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UDHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

#include "DHealthComponent.h"

UDHealthComponent::UDHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // No need to tick every frame

	// Initialize default health values
	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
}

void UDHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Reset current health to max at the start
	CurrentHealth = MaxHealth;
}

void UDHealthComponent::TakeDamage(float DamageAmount)
{
	// Avoid applying damage if the amount is zero or health is already 0
	if (DamageAmount <= 0.f || CurrentHealth <= 0.f)
		return;

	// Store old health to calculate the delta change
	const float OldHealth = CurrentHealth;

	// Reduce the health and clamp it to the range [0, MaxHealth]
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth, CurrentHealth - OldHealth);

	// If health drops to zero, trigger the death event
	if (CurrentHealth <= 0.f)
	{
		OnDeath.Broadcast();
	}
}

void UDHealthComponent::Heal(float HealAmount)
{
	// Avoid healing if the amount is zero or health is zero
	if (HealAmount <= 0.f || CurrentHealth <= 0.f)
		return;

	// Store old health to calculate the delta change
	const float OldHealth = CurrentHealth;

	// Increase health and clamp it to the range [0, MaxHealth]
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

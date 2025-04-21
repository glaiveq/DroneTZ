#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DHealthComponent.generated.h"

// Delegates for health change and death events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONETZ_API UDHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	// Take damage and update health
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float DamageAmount);

	// Heal the actor by a specified amount
	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	// Events triggered when health changes or actor dies
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;

protected:
	// Maximum health value (can be set in the editor)
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	// Current health of the actor
	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;
};

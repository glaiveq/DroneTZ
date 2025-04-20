#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DHealthComponent.generated.h"

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
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;
};

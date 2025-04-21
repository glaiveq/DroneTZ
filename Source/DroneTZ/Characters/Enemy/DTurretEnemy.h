#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DTurretEnemy.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;
class UStaticMeshComponent;
class UCapsuleComponent;
class UDProjectileShooterComponent;
class UDHealthComponent;
class UWidgetComponent;

UCLASS()
class DRONETZ_API ADTurretEnemy : public APawn
{
	GENERATED_BODY()
	
public:	
	ADTurretEnemy();

protected:
	virtual void BeginPlay() override;

public:
	UBehaviorTree* GetBehaviorTree() const;

	UStaticMeshComponent* GetTurretMesh() const;

	// Called when the turret perceives a target (such as the player or an enemy)
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

	// Initiates shooting at a target when it is perceived
	void TryShootAtTarget();

	// Updates the rotation of the health bar widget to always face the player
	void UpdateWidgetRotation();

	// Called when the turret's health changes, to update the health UI
	UFUNCTION()
	void OnTurretHealthChanged(float NewHealth, float Delta);
	
	// Called when the turret's health reaches 0, triggering its death
	UFUNCTION()
	void OnTurretDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* TurretMeshMain;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UDProjectileShooterComponent* ProjectileShooter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, Category = "Turret|Stats")
	float TurretMaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Turret|Stats")
	float TurretCurrentHealth;

	// Timer handles for managing shooting and facing player
	FTimerHandle ShootingTimerHandle;
	FTimerHandle FacePlayerTimerHandle;
};

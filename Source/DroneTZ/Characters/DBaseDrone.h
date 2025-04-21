#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DBaseDrone.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UFloatingPawnMovement;
class UDHealthComponent;
class UDAudioComponent;
class UCapsuleComponent;

UCLASS()
class DRONETZ_API ADBaseDrone : public APawn
{
	GENERATED_BODY()

	// Base class for all drone types (e.g. player and enemy drones).
	// Encapsulates shared functionality like health handling, audio, movement, etc.
	
public:
	ADBaseDrone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called when drone's health value changes. Used for reacting to damage or healing. */
	UFUNCTION()
	void OnHealthChanged(float NewHealth, float Delta);

	/** Called when drone health reaches zero. Handles death logic. */
	UFUNCTION()
	void OnDeath();

	/** Returns true if the drone is dead (health <= 0). */
	bool IsDead();

	/** Executes delayed death-related logic, e.g., level reload. */
	void HandleDeath();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> CollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone")
	TObjectPtr<USkeletalMeshComponent> DroneMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDHealthComponent> HealthComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Drone|Stats")
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Stats")
	int32 CurrentAmmo;

	FTimerHandle DeathTimerHandle;
	
};

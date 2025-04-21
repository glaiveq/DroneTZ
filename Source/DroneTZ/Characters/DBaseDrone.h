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

// The Base Drone class was created as an example so that in the future it would be possible to create enemy drones and
// not repeat some code that is common to all drones.
	
public:
	ADBaseDrone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnHealthChanged(float NewHealth, float Delta);

	UFUNCTION()
	void OnDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> RootSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> CollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone")
	TObjectPtr<USkeletalMeshComponent> DroneMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

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
	
};

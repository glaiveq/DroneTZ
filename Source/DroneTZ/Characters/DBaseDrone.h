#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DBaseDrone.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UFloatingPawnMovement;

UCLASS()
class DRONETZ_API ADBaseDrone : public APawn
{
	GENERATED_BODY()

public:
	ADBaseDrone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> RootSceneComponent;
	
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

	// Stats

	UPROPERTY(EditAnywhere, Category = "Drone|Stats")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Stats")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Drone|Stats")
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Stats")
	int32 CurrentAmmo;
};

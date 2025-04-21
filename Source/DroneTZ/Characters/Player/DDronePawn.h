#pragma once

#include "CoreMinimal.h"
#include "DroneTZ/Characters/DBaseDrone.h"
#include "GameFramework/Pawn.h"
#include "DDronePawn.generated.h"

class UDProjectileShooterComponent;
class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class DRONETZ_API ADDronePawn : public ADBaseDrone
{
	GENERATED_BODY()

public:
	ADDronePawn();

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Movement/Camera functions
	void MoveForward(float Value);
	
	void MoveRight(float Value);
	
	void MoveUp(float Value);
	
	void Turn(float Value);
	
	void LookUp(float Value);

	void Fire();

	// Handles the case when there is no ammo left
	UFUNCTION()
	void HandleShootEmpty();

public:
	virtual void Tick(float DeltaTime) override;

	UDProjectileShooterComponent* GetShooterComponent();

	void AddHealth(float Amount);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDProjectileShooterComponent* ShooterComponent;
	
	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(EditAnywhere)
	float LookSensitivity;

	UPROPERTY(EditAnywhere, Category = "Camera Tilt")
	float MaxCameraRollAngle;

	UPROPERTY(EditAnywhere, Category = "Camera Tilt")
	float CameraTiltInterpSpeed;

	FRotator TargetCameraRotation = FRotator::ZeroRotator;
};

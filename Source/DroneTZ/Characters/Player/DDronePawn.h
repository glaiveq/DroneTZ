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

	void MoveForward(float Value);
	
	void MoveRight(float Value);
	
	void MoveUp(float Value);
	
	void Turn(float Value);
	
	void LookUp(float Value);

	void Fire();

	UFUNCTION()
	void HandleShootEmpty();

public:
	virtual void Tick(float DeltaTime) override;

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

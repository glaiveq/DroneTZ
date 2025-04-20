#include "DDronePawn.h"
#include "DroneTZ/UI/HUD/DDroneHUD.h"
#include "DroneTZ/Camera/DDroneShootCameraShake.h"
#include "DroneTZ/ShootingSystem/DProjectileShooterComponent.h"
#include "DroneTZ/Audio/DAudioComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"

ADDronePawn::ADDronePawn()
{
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    bUseControllerRotationYaw = true;

    ShooterComponent = CreateDefaultSubobject<UDProjectileShooterComponent>(TEXT("ShooterComponent"));

    // Setting some stats
    MoveSpeed = 10.f;
    LookSensitivity = 1.f;
    MaxCameraRollAngle = 2.5f;
    CameraTiltInterpSpeed = 5.f;
}

void ADDronePawn::BeginPlay()
{
    Super::BeginPlay();
}

void ADDronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ADDronePawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADDronePawn::MoveRight);
    PlayerInputComponent->BindAxis("MoveUp", this, &ADDronePawn::MoveUp);
    PlayerInputComponent->BindAxis("Turn", this, &ADDronePawn::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ADDronePawn::LookUp);
    
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADDronePawn::Fire);
}

void ADDronePawn::MoveForward(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
    }
}

void ADDronePawn::MoveRight(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorRightVector(), Value * MoveSpeed);
    }
}

void ADDronePawn::MoveUp(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorUpVector(), Value * MoveSpeed);
    }
}

void ADDronePawn::Turn(float Value)
{
    AddControllerYawInput(Value * LookSensitivity);
}

void ADDronePawn::LookUp(float Value)
{
    AddControllerPitchInput(Value * LookSensitivity);
}

void ADDronePawn::Fire()
{
    if (ShooterComponent)
    {
        ShooterComponent->ShootProjectile();
    }

    if (AudioComponent)
    {
        AudioComponent->PlayShootSound();
    }
    
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (PC->PlayerCameraManager)
        {
            PC->PlayerCameraManager->StartCameraShake(UDDroneShootCameraShake::StaticClass());
        }
    }
}

void ADDronePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const float RightInput = InputComponent->GetAxisValue("MoveRight");

    const float TargetRoll = FMath::Clamp(RightInput * MaxCameraRollAngle, -MaxCameraRollAngle, MaxCameraRollAngle);

    TargetCameraRotation = FMath::RInterpTo(TargetCameraRotation, FRotator(0.f, 0.f, TargetRoll), DeltaTime, CameraTiltInterpSpeed);

    if (Camera)
    {
        Camera->SetRelativeRotation(TargetCameraRotation);
    }

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ADDroneHUD* HUD = Cast<ADDroneHUD>(PC->GetHUD()))
        {
            HUD->UpdateAmmoDisplay(ShooterComponent->GetCurrentAmmo(), ShooterComponent->GetMaxAmmo());
        }
    }
}

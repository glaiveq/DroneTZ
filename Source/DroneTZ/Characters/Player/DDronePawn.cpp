#include "DDronePawn.h"
#include "DroneTZ/UI/HUD/DDroneHUD.h"
#include "DroneTZ/Camera/DDroneShootCameraShake.h"
#include "DroneTZ/ShootingSystem/DProjectileShooterComponent.h"
#include "DroneTZ/Audio/DAudioComponent.h"
#include "DroneTZ/Health/DHealthComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"

ADDronePawn::ADDronePawn()
{
    // Automatically possess the player when the game starts
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    bUseControllerRotationYaw = true;

    // Initialize shooter component for projectile shooting
    ShooterComponent = CreateDefaultSubobject<UDProjectileShooterComponent>(TEXT("ShooterComponent"));

    // Default settings for movement speed, sensitivity, camera tilt, and interpolation speed
    MoveSpeed = 10.f;
    LookSensitivity = 1.f;
    MaxCameraRollAngle = 2.5f;
    CameraTiltInterpSpeed = 5.f;
}

void ADDronePawn::BeginPlay()
{
    Super::BeginPlay();

    // Bind the event for empty ammo to the corresponding handler
    ShooterComponent->OnShootEmpty.AddDynamic(this, &ADDronePawn::HandleShootEmpty);
}

void ADDronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind player input actions and axes to movement and control functions
    PlayerInputComponent->BindAxis("MoveForward", this, &ADDronePawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADDronePawn::MoveRight);
    PlayerInputComponent->BindAxis("MoveUp", this, &ADDronePawn::MoveUp);
    PlayerInputComponent->BindAxis("Turn", this, &ADDronePawn::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ADDronePawn::LookUp);

    // Bind fire action
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
    // Check if shooter component exists and fire a projectile
    if (ShooterComponent && ShooterComponent->ShootProjectile())
    {
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
}

void ADDronePawn::HandleShootEmpty()
{
    if (AudioComponent)
    {
        AudioComponent->PlayEmptyClipSound();
    }
}

UDProjectileShooterComponent* ADDronePawn::GetShooterComponent()
{
    return ShooterComponent;
}

void ADDronePawn::AddHealth(float Amount)
{
    if (HealthComponent)
    {
        HealthComponent->Heal(Amount);
    }
}

void ADDronePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Handle camera roll based on right input (e.g., for tilt effect)
    const float RightInput = InputComponent->GetAxisValue("MoveRight");
    const float TargetRoll = FMath::Clamp(RightInput * MaxCameraRollAngle, -MaxCameraRollAngle, MaxCameraRollAngle);
    TargetCameraRotation = FMath::RInterpTo(TargetCameraRotation, FRotator(0.f, 0.f, TargetRoll), DeltaTime, CameraTiltInterpSpeed);

    if (Camera)
    {
        Camera->SetRelativeRotation(TargetCameraRotation);
    }

    // Update the ammo display on the HUD
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ADDroneHUD* HUD = Cast<ADDroneHUD>(PC->GetHUD()))
        {
            HUD->UpdateAmmoDisplay(ShooterComponent->GetCurrentAmmo(), ShooterComponent->GetMaxAmmo());
        }
    }
}

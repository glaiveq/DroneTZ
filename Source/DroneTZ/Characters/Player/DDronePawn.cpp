#include "DDronePawn.h"
#include "Components/StaticMeshComponent.h"

ADDronePawn::ADDronePawn()
{
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    bUseControllerRotationYaw = true;

    // Setting some stats
    MoveSpeed = 10.f;
    LookSensitivity = 1.f;
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
}

void ADDronePawn::MoveForward(float Value)
{
    if (Value != 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), Value);
        AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
    }
}

void ADDronePawn::MoveRight(float Value)
{
    if (Value != 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveRight: %f"), Value);
        AddMovementInput(GetActorRightVector(), Value * MoveSpeed);
    }
}

void ADDronePawn::MoveUp(float Value)
{
    if (Value != 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveUp: %f"), Value);
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

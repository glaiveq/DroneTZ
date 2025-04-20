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

	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

	void TryShootAtTarget();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* CollisionComponent;

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

	FTimerHandle ShootingTimerHandle;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;


UENUM()
enum class EFiringStates : uint8
{
	Reloading,
	Aiming,
	Locked
};


// Holds barrel properties and Elevate method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region UE

	// Sets default values for this component's properties
	UTankAimingComponent();

#pragma endregion UE

	bool AimAt(FVector HitLocation);


	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStates FiringState = EFiringStates::Reloading;

private:
#pragma region UE

	virtual void BeginPlay()override;
	virtual void TickComponent(float DeltatTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

#pragma endregion UE


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSecs = 3.0;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 6000;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);


	double LastFireTime = FPlatformTime::Seconds();
};

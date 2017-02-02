// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward declaration
class UTankBarrel;
class UTankTurret;


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
	// Sets default values for this component's properties
	UTankAimingComponent();

	bool AimAt(FVector HitLocation, float Speed);



	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStates FiringState = EFiringStates::Locked;


private:


	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);
};

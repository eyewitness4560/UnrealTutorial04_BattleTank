// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"

#include "TankAimingComponent.h"

#pragma region UE


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

#pragma endregion UE


bool UTankAimingComponent::AimAt(FVector HitLocation, float Speed)
{
	if (!Barrel || !Turret) return false;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto OurTankName = GetOwner()->GetName();
	auto TankBarrelEnd = Barrel->GetComponentLocation().ToString();
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, Speed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace); // last 4 vars are not really included in the video

	if (bHaveAimSolution)
	{
		auto DesiredAimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(DesiredAimDirection);
		MoveTurret(DesiredAimDirection);
	}
	return bHaveAimSolution;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) return;
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotation;

	//UE_LOG(LogTemp, Warning, TEXT(" Turret aiming at %s "), *AimDirection.ToString());

	Turret->Turn(DeltaRotator.Yaw);

}


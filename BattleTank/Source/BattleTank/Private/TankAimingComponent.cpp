// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"

#include "TankAimingComponent.h"

#pragma region UE

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	//UE_LOG(LogTemp, Warning, TEXT("BeginPlayOnTankAimingComponent"));
}

void UTankAimingComponent::TickComponent(float DeltatTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltatTime, TickType, ThisTickFunction);
	if (AmmoCount <= 0)
	{
		FiringState = EFiringStates::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSecs)
	{
		FiringState = EFiringStates::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStates::Aiming;
	}
	else
	{
		FiringState = EFiringStates::Locked;
	}

	//UE_LOG(LogTemp, Warning, TEXT("TickOnTankAimingComponent"));
}


#pragma endregion UE

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) return;
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) return false;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));


	auto OurTankName = GetOwner()->GetName();
	auto TankBarrelEnd = Barrel->GetComponentLocation().ToString();
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace); // last 4 vars are not really included in the video

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel();
		MoveTurret();
	}

	return bHaveAimSolution;
}
void UTankAimingComponent::Fire()
{


	if (FiringState != EFiringStates::Reloading && FiringState != EFiringStates::OutOfAmmo)
	{
		if (!ensure(Barrel)) return;

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoCount--;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.05f);
}

void UTankAimingComponent::MoveBarrel()
{
	if (!ensure(Barrel)) return;

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);

}
void UTankAimingComponent::MoveTurret()
{
	if (!ensure(Turret)) return;
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotation;
	auto RotationF = DeltaRotator.Yaw;

	if (RotationF > 180.f)
		RotationF = 180 - RotationF;
	else if (RotationF < -180.f)
		RotationF = 360 + RotationF;


	//UE_LOG(LogTemp, Warning, TEXT(" Turret aiming at %s "), *AimDirection.ToString());


	//UE_LOG(LogTemp, Warning, TEXT(" TurrRot: %f"), RotationF);

	Turret->Turn(RotationF);

}

EFiringStates UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}


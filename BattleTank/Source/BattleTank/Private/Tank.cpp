// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleTank.h"

#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/TankAimingComponent.h"
#include "Public/Projectile.h"

#include "Tank.h"


#pragma region UE

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

#pragma endregion UE



void ATank::Fire()
{

	bool IsReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecs);

	if (Barrel && IsReloaded)
	{
		//spawn projectile at the socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		UE_LOG(LogTemp, Warning, TEXT("Launched "));
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::Initialize(UTankAimingComponent * AimingComponentToSet, UTankBarrel * BarrelToSet)
{
	if (!ensure(AimingComponentToSet && BarrelToSet)) return;
	TankAimingComponent = AimingComponentToSet;
	Barrel = BarrelToSet;
}

UTankAimingComponent* ATank::GetTankAimingComponent() const
{
	return TankAimingComponent;
}

void ATank::AimAt(FVector HitLocation)
{
	bool CurrentAimingSolution = TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	if (CurrentAimingSolution != HasAimingSolution)
	{
		HasAimingSolution = CurrentAimingSolution;
	}
}


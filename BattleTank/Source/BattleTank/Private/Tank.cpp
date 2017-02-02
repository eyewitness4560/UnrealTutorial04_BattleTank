// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleTank.h"

#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "Public/Projectile.h"

#include "Tank.h"


#pragma region UE

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	// no need to protect pointers as added as construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));

}

#pragma endregion UE



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponentParameters)
{
	Super::SetupPlayerInputComponent(InputComponentParameters);
}


#pragma region DelegatedStuff

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SeTTurretReference(TurretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Launched"));

	bool IsReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecs);

	if (Barrel &&IsReloaded)
	{
		//spawn projectile at the socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}


void ATank::AimAt(FVector HitLocation)
{
	bool CurrentAimingSolution = TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	if (CurrentAimingSolution != HasAimingSolution)
	{
		HasAimingSolution = CurrentAimingSolution;
		OnAimingSolutionChange.Broadcast(HasAimingSolution);
	}
}

#pragma endregion DelegatedStuff


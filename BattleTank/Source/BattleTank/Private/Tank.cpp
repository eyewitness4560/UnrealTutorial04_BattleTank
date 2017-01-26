// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleTank.h"

#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/TankAimingComponent.h"

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
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SeTTurretReference(TurretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("1 2 3"));
	UE_LOG(LogTemp, Error, TEXT("Fire!"));
	UE_LOG(LogTemp, Warning, TEXT("Hey!"));
	UE_LOG(LogTemp, Warning, TEXT("Hey!"));
	UE_LOG(LogTemp, Warning, TEXT("Hey!"));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}



#pragma endregion DelegatedStuff


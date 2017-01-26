// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleTank.h"

#include "Public/TankBarrel.h"
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


void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}


void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
}



#pragma endregion DelegatedStuff


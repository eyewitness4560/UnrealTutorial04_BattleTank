// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


#pragma region UE




// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// no need to protect pointers as added as construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}



#pragma endregion UE



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponentParameters)
{
	Super::SetupPlayerInputComponent(InputComponentParameters);
}



#pragma region DelegatedStuff


void ATank::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}


void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
}



#pragma endregion DelegatedStuff


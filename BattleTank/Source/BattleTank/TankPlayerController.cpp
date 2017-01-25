// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BattleTank.h"
#include "TankPlayerController.h"

#pragma region UE4 Begin, Tick
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetControlledTank() == nullptr) { UE_LOG(LogTemp, Error, TEXT("NoControlledTankAvailable!")); return; }

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControlle BeginPlay on %s"), *GetControlledTank()->GetName());
	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("TickDelta: %f"), DeltaTime);
}
#pragma endregion UE4 Begin, Tick

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	//GetWorldLoc through cross hair
		//if it hits something
			// aim at the point

}


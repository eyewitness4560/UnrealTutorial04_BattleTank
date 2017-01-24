// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetControlledTank() == nullptr) { UE_LOG(LogTemp, Error, TEXT("NoControlledTankAvailable!")); return; }

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControlle BeginPlay on %s"), *GetControlledTank()->GetName());
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


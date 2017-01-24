// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank()) { UE_LOG(LogTemp, Error, TEXT("NoControlledTankAvailable!")); return; }

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay on %s"), *GetControlledTank()->GetName());
	}

	if (!GetPlayerTank()) { UE_LOG(LogTemp, Warning, TEXT("PlayerTankNotFound FirstPlayer %s")); return; }
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FoundPlayer! %s , by %s"), *GetPlayerTank()->GetName(), *GetControlledTank()->GetName());
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn){return nullptr;}
		return Cast<ATank>(PlayerPawn);
}

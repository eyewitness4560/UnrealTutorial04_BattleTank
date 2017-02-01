// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BattleTank.h"

#include "Public/Tank.h"

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// move towards the player

		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// fire if ready

		ControlledTank->Fire();
	}
}





// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BattleTank.h"

#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"

#include "TankAIController.h"

#pragma region UE

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))return;

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank))return;

		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::HandleOnDeathEvent);

		// subscribe our local method to the tank's death event
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank))return;

	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringStates::Locked)
		AimingComponent->Fire();
}

#pragma endregion


void ATankAIController::HandleOnDeathEvent()
{
	auto Pawn = GetPawn();
	if (!Pawn) return;
	Pawn->DetachFromControllerPendingDestroy();

	UE_LOG(LogTemp, Warning, TEXT("DEATH HANDLE in AI controller"));
}


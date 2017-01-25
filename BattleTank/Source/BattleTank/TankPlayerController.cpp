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
	//UE_LOG(LogTemp, Warning, TEXT("TickDelta: %f"), DeltaTime);
	AimTowardsCrosshair();
}
#pragma endregion UE4 Begin, Tick

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;


	FVector HitLocation; //OUT parameter

	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

	if (GetSightRayHitLocation(HitLocation))  //has a side effect that's going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *HitLocation.ToString());
		//if it hits something
			// aim at the point
	}
}

// get world location of line trace through cross hair
bool ATankPlayerController::GetSightRayHitLocation(FVector& Hit) const
{
	//Find cross hair position

	Hit = FVector(ScreenLocation(),0.f);
	
	// "DE project" screen position to world direction
	//line trace through the projection, see what we hit (up to max range)
	

	return	true;
}

FVector2D ATankPlayerController::ScreenLocation() const
{
	int32 ViewportSizeX = 0;
	int32 ViewportSizeY = 0;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	return FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
}

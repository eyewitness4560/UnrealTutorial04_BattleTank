// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BattleTank.h"

#include "Public/TankAimingComponent.h"

#include "TankPlayerController.h"

#pragma region UE4 Begin, Tick
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))	{FoundAimingComponent(AimingComponent);		}
	else	{UE_LOG(LogTemp, Error, TEXT("No aiming component found!"))	return;	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("TickDelta: %f"), DeltaTime);
	AimTowardsCrosshair();
}
#pragma endregion UE4 Begin, Tick

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) return;


	FVector HitLocation; //OUT parameter

	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

	if (GetSightRayHitLocation(HitLocation))  //has a side effect that's going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{

	FVector CamWorldLoc;
	FVector LookDir;
	if (GetLookDirection(LookDir, CamWorldLoc))
	{
		if (GetLookVectorHitLocation(LookDir, CamWorldLoc, HitLocation))
			return true;

	}
	//line trace through the projection, see what we hit (up to max range)




	return	false;
}
FVector2D ATankPlayerController::ScreenLocation() const
{
	int32 ViewportSizeX = 0;
	int32 ViewportSizeY = 0;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	return FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
}
bool ATankPlayerController::GetLookDirection(FVector& LookDir, FVector& CamWorldLoc) const
{
	return DeprojectScreenPositionToWorld(ScreenLocation().X, ScreenLocation().Y, CamWorldLoc, LookDir);
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& CameraWorldLocation, FVector& Hit) const
{
	FHitResult HitRes;
	FCollisionQueryParams Params = FCollisionQueryParams(FName(NAME_None), false);
	if (GetWorld()->LineTraceSingleByChannel(HitRes, CameraWorldLocation, CameraWorldLocation + LookDirection*LineTraceRange, ECollisionChannel::ECC_Visibility, Params))
	{
		Hit = HitRes.Location;
		return true;
	}
	Hit = FVector(0);
	return false;
}

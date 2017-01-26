// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"


#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel right amount per frame
	// given max elevation speed

	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed,-1,1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation), 0, 0));

	auto time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("BarrelElevate() called at: %f speed: %f"), time, RelativeSpeed);
}

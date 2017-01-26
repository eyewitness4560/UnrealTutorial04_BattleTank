// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"


#include "TankTurret.h"




void UTankTurret::Turn(float RelativeSpeed)
{

	auto TurnChange = FMath::Clamp<float>(RelativeSpeed, -1, 1)* MaxDegreesPerSecond* GetWorld()->DeltaTimeSeconds;

	auto RawNewTurn = RelativeRotation.Yaw + TurnChange;

	SetRelativeRotation(FRotator(0, RawNewTurn, 0), 0, 0);


	auto time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("BarrelTurn() called at: %f speed: %f"), time, RelativeSpeed);

}

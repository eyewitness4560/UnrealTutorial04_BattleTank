// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"


#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel right amount per frame
	// given max elevation speed

	auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("BarrelElevate() called at: %f speed: %f"), time, RelativeSpeed);
}

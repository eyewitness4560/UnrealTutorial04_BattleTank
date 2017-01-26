// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"


#include "TankBarrel.h"




void UTankBarrel::Elevate(float DegreesPerSec)
{
	// move the barrel right amount per frame
	// given max elevation speed

	UE_LOG(LogTemp, Warning, TEXT("BarrelElevate() called at speed %f"),DegreesPerSec);
}

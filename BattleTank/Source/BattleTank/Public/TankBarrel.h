// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float DegreesPerSec);


private:

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 4;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinElevation = -10;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxElevation = 30;

};

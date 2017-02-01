// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force and to apply forces to the tank
 */

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle);

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 100000; //this is max force per track in newtons
};

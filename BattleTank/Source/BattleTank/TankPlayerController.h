// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"
#include "TankPlayerController.generated.h" //must be last included

/**
 *
 */
UCLASS()

class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick(float) override;

private:
	//move the tank barrel towards the cross hair would hit the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector & Hit) const;
};

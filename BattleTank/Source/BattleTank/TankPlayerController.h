// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be last included

class ATank;
class UTankAimingComponent;

/**
 *
 */
UCLASS()

class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossHairYLocation = 0.3333333f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LineTraceRange = 1000000;



	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	//move the tank barrel towards the cross hair would hit the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &) const;

	FVector2D ScreenLocation() const;

	bool GetLookDirection(FVector&, FVector&) const;

	bool GetLookVectorHitLocation(FVector&, FVector&, FVector&) const;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingCompRef);
};

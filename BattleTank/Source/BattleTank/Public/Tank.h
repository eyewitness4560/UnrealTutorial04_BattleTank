// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankAimingComponent;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

#pragma region Ue

	// Sets default values for this pawn's properties
	ATank();

#pragma endregion Ue

	UPROPERTY(EditAnywhere)
	float LaunchSpeed = 10000; // TODO: FindSensibleDefault




	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);


protected:

	UTankAimingComponent* TankAimingComponent = nullptr;

};

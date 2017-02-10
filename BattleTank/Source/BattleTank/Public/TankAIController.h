// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"


#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 *
 */
UCLASS()

class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
#pragma region UE

	virtual void Tick(float) override;

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

#pragma endregion UE

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 3000.0f;

	UTankAimingComponent* AimingComponent = nullptr;

	UFUNCTION()
	void HandleOnDeathEvent();
};

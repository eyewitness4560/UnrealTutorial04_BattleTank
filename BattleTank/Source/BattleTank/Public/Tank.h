// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

#pragma region Ue

	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay();

#pragma endregion Ue


	//TODO: remove after fire has been removed from class
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 6000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSecs = 3.0;

	double LastFireTime = FPlatformTime::Seconds();


	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;



	UFUNCTION(BLueprintCallable, Category = "Setup")
		UTankAimingComponent* GetTankAimingComponent() const;

protected:

	UTankAimingComponent * TankAimingComponent = nullptr;
	UTankBarrel * Barrel = nullptr;
	
};

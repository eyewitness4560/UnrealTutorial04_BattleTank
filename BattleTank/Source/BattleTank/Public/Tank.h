// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAimingSolutionChange, bool, AimingSolutionFound);

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
	float LaunchSpeed = 6000; 




	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UPROPERTY(BlueprintAssignable,Category="Aiming")
	FOnAimingSolutionChange OnAimingSolutionChange;


protected:

	bool HasAimingSolution = false;



	UTankAimingComponent* TankAimingComponent = nullptr;

};

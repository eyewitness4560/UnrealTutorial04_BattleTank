// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"


#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

#pragma region Ue

	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay();

	virtual float TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	FOnDeath OnDeath;

#pragma endregion Ue


protected:

	float CurrentHealth = 100.0f;
	float MaxHealth = 100.0f;

};

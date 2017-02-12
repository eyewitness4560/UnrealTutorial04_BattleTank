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


#pragma region Ue

	ATank();
	virtual void BeginPlay() override;

#pragma endregion Ue

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
	
	virtual float TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	FOnDeath OnDeath;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100.0f;

};

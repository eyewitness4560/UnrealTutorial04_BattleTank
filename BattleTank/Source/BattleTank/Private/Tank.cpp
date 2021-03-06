// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleTank.h"


#include "Tank.h"


#pragma region UE

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

#pragma endregion UE

float ATank::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = FMath::Clamp(Damage, 0.0f, CurrentHealth);
	CurrentHealth -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Damaged %f"), CurrentHealth);
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return DamageToApply;
}


float ATank::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}


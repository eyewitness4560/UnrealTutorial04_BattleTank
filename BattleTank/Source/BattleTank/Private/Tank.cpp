// Fill out your copyright notice in the Description page of Project Settings.



#include "BattleTank.h"


#include "Tank.h"


#pragma region UE

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion UE




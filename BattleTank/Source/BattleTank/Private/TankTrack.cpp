// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float throttle)
{
	auto ForceApplied = GetForwardVector()*FMath::Clamp(throttle, -1.f, 1.f) * (TrackMaxDrivingForce / 2.0f);

	FVector ForceOffset = FVector().ForwardVector * FVector(2000);

	auto ForceLocationFwd = GetComponentLocation() + ForceOffset;
	auto ForceLocationRwd = GetComponentLocation() - ForceOffset;


	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocationFwd);
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocationRwd);
}

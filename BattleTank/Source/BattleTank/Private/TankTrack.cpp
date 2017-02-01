// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float throttle)
{
	UE_LOG(LogTemp, Warning, TEXT(" %s Throttle set to %f"), *GetOwner()->GetName(), throttle);

	auto ForceApplied = GetForwardVector()*throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}

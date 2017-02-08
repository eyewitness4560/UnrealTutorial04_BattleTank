// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"





#pragma region UE

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); //registered the OnHit event
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplySidewaysForce();
	DriveTrack();
	CurrentThrottle = 0.0f;

	//UE_LOG(LogTemp,Warning,TEXT(" TrackOnGround %f"),GetWorld()->TimeSeconds)
}

void UTankTrack::ApplySidewaysForce()
{
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	auto RightDirection = GetRightVector();
	auto MovementDirection = GetComponentVelocity();

	auto SlippageSpeed = FVector::DotProduct(RightDirection, MovementDirection);

	auto CorrectionAccel = SlippageSpeed / DeltaTime * -RightDirection;

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto correctiveForce = TankRoot->GetMass()*CorrectionAccel / 2;

	TankRoot->AddForce(correctiveForce);
}

#pragma endregion UE

void UTankTrack::SetThrottle(float throttle)
{
	CurrentThrottle = FMath::Clamp(CurrentThrottle + throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector()*FMath::Clamp(CurrentThrottle, -1.f, 1.f) * (TrackMaxDrivingForce / 2.0f);

	FVector ForceOffset = FVector().ForwardVector * FVector(300);

	auto ForceLocationFwd = GetComponentLocation() + ForceOffset;
	auto ForceLocationRwd = GetComponentLocation() - ForceOffset;


	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocationFwd);
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocationRwd);
}


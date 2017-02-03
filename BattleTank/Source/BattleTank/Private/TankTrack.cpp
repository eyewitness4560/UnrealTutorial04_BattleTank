// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"





#pragma region UE

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); //registered the OnHit event

}

void UTankTrack::TickComponent(float DeltatTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto RightDirection = GetRightVector();
	auto MovementDirection = GetComponentVelocity();

	auto SlippageSpeed = FVector::DotProduct(RightDirection, MovementDirection);

	auto CorrectionAccel = SlippageSpeed / DeltatTime * -RightDirection;

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto correctiveForce = TankRoot->GetMass()*CorrectionAccel / 2;

	TankRoot->AddForce(correctiveForce);

}
void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("ANY¡¡¡¡D"));
}

#pragma endregion UE

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


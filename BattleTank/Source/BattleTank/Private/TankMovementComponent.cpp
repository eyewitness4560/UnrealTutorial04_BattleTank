// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "Public/TankTrack.h"

#include "TankMovementComponent.h"




void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));

	auto RightThrow = FVector::CrossProduct(AIForwardIntention, TankForward).Z;

	IntendTurnRight(FMath::Clamp((RightThrow*100.f), -1.f, 1.f));

	//UE_LOG(LogTemp, Warning, TEXT(" %s movement direction is %s"), *GetOwner()->GetName(), *(AIForwardIntention.ToString()));
	GoThisWay = AIForwardIntention;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	this->LeftTrack->SetThrottle(-Throw);
	this->RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) return;

	LeftTrack = LeftTrackToSet;

	RightTrack = RightTrackToSet;

}

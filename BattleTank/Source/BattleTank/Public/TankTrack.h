// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"

#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force and to apply forces to the tank
 */

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
#pragma region UEPublic
	UTankTrack();


#pragma endregion UEPublic
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle);

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 100000; //this is max force per track in newtons

private:
#pragma region UEPrivate

	virtual void BeginPlay()override;
	virtual void TickComponent(float DeltatTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

#pragma endregion UEPrivate

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};

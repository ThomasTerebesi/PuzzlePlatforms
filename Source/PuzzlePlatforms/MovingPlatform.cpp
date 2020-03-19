// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	speed = 10.0;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		// these should not be called by the client
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	globalStartLocation = GetActorLocation();
	globalTargetLocation = GetTransform().TransformPosition(targetLocation);
}

void AMovingPlatform::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (HasAuthority())	// '!HasAuthority()' refers to the client only
	{
		FVector location = GetActorLocation();
		FVector direction = (globalTargetLocation - globalStartLocation).GetSafeNormal();

		if (FVector::PointsAreNear(location, globalTargetLocation, 20.0))
		{
			UE_LOG(LogTemp, Warning, TEXT("SWAPPING!"));

			FVector temp = globalTargetLocation;
			globalTargetLocation = globalStartLocation;
			globalStartLocation = temp;
		}

		location += direction * speed * deltaTime;
		SetActorLocation(location);
	}
}

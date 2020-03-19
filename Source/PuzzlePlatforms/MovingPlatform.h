// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Platform")
	float speed;

	UPROPERTY(EditAnywhere, Category = "Moving Platform", Meta = (MakeEditWidget = true))	// 'BlueprintReadWrite' for some reason cancels out the 'MakeEditWidget' metadata specifier
	FVector targetLocation;

private:
	FVector globalTargetLocation;
	FVector globalStartLocation;
};

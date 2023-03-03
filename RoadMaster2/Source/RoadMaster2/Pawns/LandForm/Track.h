// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandFormPawn.h"
#include "Track.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API ATrack : public ALandFormPawn
{
	GENERATED_BODY()
public:

	ATrack();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "SplineLine")
	class USplineComponent* SplineComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "SplineLine")
	class UTimelineComponent* TimelineComponent;	

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "SplineLine")
	TArray<AMovableUnits*> UnitList;
};

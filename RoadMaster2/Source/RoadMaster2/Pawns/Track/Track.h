// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API ATrack : public APawn
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

	//获取方向值，+1为从起点进入，-1为从终点进入
	UFUNCTION(BlueprintCallable)
	int32 GetDirectionIntForUnit(AMovableUnits* unit);
};

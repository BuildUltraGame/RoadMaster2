// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track.generated.h"

USTRUCT(BlueprintType)
struct FUnitMoveState
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	AMovableUnits* Unit;

	UPROPERTY(BlueprintReadWrite)
	int32 Direction;

	UPROPERTY(BlueprintReadWrite)
	float CurrentMoveTime;

	UPROPERTY(BlueprintReadWrite)
	float MaxMoveTime;
};

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

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "SplineLine",Replicated)
	TArray<FUnitMoveState> UnitMoveList;

	//获取方向值，+1为从起点进入，-1为从终点进入
	UFUNCTION(BlueprintCallable)
	int32 GetDirectionIntForUnit(AMovableUnits* unit);

	UFUNCTION(BlueprintCallable)
	void AddUnitToTrack(AMovableUnits* unit);

	UFUNCTION(BlueprintCallable)
	void RemoveUnitFromTrack(AMovableUnits* unit);

	virtual void Tick(float DeltaSeconds) override;

	
};

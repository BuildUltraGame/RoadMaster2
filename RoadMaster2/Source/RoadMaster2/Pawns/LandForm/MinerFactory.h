// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandFormPawn.h"
#include "MinerFactory.generated.h"

class UUnitSpawnerComponent;
/**
 * 
 */
UCLASS()
class ROADMASTER2_API AMinerFactory : public ALandFormPawn
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	UUnitSpawnerComponent* UnitSpawner;

	UFUNCTION(BlueprintCallable)
	void SpawnUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnSelectStartPoint(UPrimitiveComponent* TouchedComponent ,FKey ButtonPressed);
};

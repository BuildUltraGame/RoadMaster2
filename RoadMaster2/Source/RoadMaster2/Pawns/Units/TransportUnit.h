// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovableUnits.h"
#include "TransportUnit.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API ATransportUnit : public AMovableUnits
{
	GENERATED_BODY()

public:
	virtual void InitUnitByType(ALandFormPawn* StartLand, FVector InDestination) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
};

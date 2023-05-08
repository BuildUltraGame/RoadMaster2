// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandFormPawn.h"
#include "Destination.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API ADestination : public ALandFormPawn
{
	GENERATED_BODY()

public:
	virtual bool ExecLandformEffect(AMovableUnits* Unit) override;

protected:
	virtual void BeginPlay() override;
};

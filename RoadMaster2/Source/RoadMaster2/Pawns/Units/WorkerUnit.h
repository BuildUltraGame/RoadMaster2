// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovableUnits.h"
#include "WorkerUnit.generated.h"

class ATrafficSignActor;
/**
 * 
 */
UCLASS()
class ROADMASTER2_API AWorkerUnit : public AMovableUnits
{
	GENERATED_BODY()

public:
	ATrafficSignActor* TargetSign;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;

	virtual bool ExecUnitToLandformEffect(ALandFormPawn* LandForm) override;

	AWorkerUnit();
};

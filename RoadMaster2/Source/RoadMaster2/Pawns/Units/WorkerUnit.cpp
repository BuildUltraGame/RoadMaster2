// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerUnit.h"

void AWorkerUnit::InitUnitByType(ALandFormPawn* StartLand, FVector InDestination)
{
	Super::InitUnitByType(StartLand, InDestination);
	MustMoveOnLine = true;
	IsStopAtDestination = true;
}

void AWorkerUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);
}

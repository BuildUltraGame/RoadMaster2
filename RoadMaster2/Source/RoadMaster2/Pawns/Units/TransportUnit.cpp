// Fill out your copyright notice in the Description page of Project Settings.


#include "TransportUnit.h"

void ATransportUnit::InitUnitByType(ALandFormPawn* StartLand, FVector InDestination)
{
	Super::InitUnitByType(StartLand, InDestination);
	MustMoveOnLine = true;
	IsStopAtDestination = true;
}

void ATransportUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);
}

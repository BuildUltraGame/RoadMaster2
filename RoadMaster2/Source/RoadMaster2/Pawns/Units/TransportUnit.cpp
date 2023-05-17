// Fill out your copyright notice in the Description page of Project Settings.


#include "TransportUnit.h"

ATransportUnit::ATransportUnit()
{
	MustMoveOnLine = true;
	IsStopAtDestination = true;
	JamAble = true;
}

void ATransportUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);
}

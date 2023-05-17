// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerUnit.h"

#include "RoadMaster2/Pawns/LandForm/LandFormPawn.h"

AWorkerUnit::AWorkerUnit()
{
	MustMoveOnLine = true;
	IsStopAtDestination = true;
	JamAble = false;
}

void AWorkerUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);
}

bool AWorkerUnit::ExecUnitToLandformEffect(ALandFormPawn* LandForm)
{
	//扳动道闸
	if (LandForm->WorkAble)
	{
		
	}
	return Super::ExecUnitToLandformEffect(LandForm);
}

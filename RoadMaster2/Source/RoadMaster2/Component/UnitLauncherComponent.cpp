// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitLauncherComponent.h"

#include "RoadMaster2/Units/MovableUnits.h"

void UUnitLauncherComponent::ChangeNavigator(AMovableUnits* Unit)
{
	if (LandFormOwner && Unit)
	{
		if (Unit&&Unit->CanBeLaunched)
		{
			ALandFormPawn* NextLandForm = LandFormOwner->GetTargetPointByInput(Unit);
			Unit->Navigator->Navigate(LandFormOwner,NextLandForm);
		}
	}
	//UE_LOG()
}

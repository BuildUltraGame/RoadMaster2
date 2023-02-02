// Fill out your copyright notice in the Description page of Project Settings.


#include "NavigationComponent.h"
#include "RoadMaster2/Units/MovableUnits.h"

void UNavigationComponent::InitNavigator(AMovableUnits* Owner)
{
	OwnerUnit = Owner;
	StartLand = OwnerUnit->Spawner;
}

void UNavigationComponent::Navigate(ALandFormPawn* Destination)
{
	EndLand = Destination;
	if (OwnerUnit)
	{
		if (IsValid(StartLand) && IsValid(EndLand))
		{
			const FVector StartPoint = StartLand->GetWayPoint();
			const FVector EndPoint = EndLand->GetWayPoint();
			OwnerUnit->AddMovementInput(EndPoint-StartPoint,OwnerUnit->LinearSpeed);
		}
	}
}


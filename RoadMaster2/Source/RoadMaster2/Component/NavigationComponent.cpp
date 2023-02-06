// Fill out your copyright notice in the Description page of Project Settings.


#include "NavigationComponent.h"
#include "RoadMaster2/Pawns/Units/MovableUnits.h"

void UNavigationComponent::InitNavigator(AMovableUnits* Owner)
{
	OwnerUnit = Owner;
	StartLand = OwnerUnit->Spawner;
}

void UNavigationComponent::Navigate(ALandFormPawn* Start,ALandFormPawn* Destination)
{
	EndLand = Destination;
	StartLand = Start;
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


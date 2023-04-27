// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"

#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "RoadMaster2/Pawns/Units/MovableUnits.h"

ATrack::ATrack()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
}

int32 ATrack::GetDirectionIntForUnit(AMovableUnits* unit)
{
	if (IsValid(SplineComponent))
	{
		const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
		const FVector EndLocation = SplineComponent->GetLocationAtSplinePoint(NumPoints - 1, ESplineCoordinateSpace::World);
		const FVector StartLocation = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		const FVector UnitLocation = unit->GetActorLocation();
		const float DistanceStart = FVector::Distance(UnitLocation, StartLocation);
		const float DistanceEnd = FVector::Distance(UnitLocation, EndLocation);
		if (DistanceEnd >DistanceStart)
		{
			return 1;
		}
		return -1;
	}
	UE_LOG(LogTemp, Display, TEXT("GetDirectionIntForUnit --- No Splite Line"));
	return 0;
}

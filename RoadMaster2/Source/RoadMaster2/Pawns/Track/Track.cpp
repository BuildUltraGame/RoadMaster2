// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"

#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "Net/UnrealNetwork.h"
#include "RoadMaster2/Pawns/Units/MovableUnits.h"
#include "RoadMaster2/Tools/RMBlueprintFunctionLibrary.h"

ATrack::ATrack()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
}


void ATrack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATrack,UnitMoveList);
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

void ATrack::AddUnitToTrack(AMovableUnits* unit)
{	
	if (IsValid(unit))
	{
		for (auto Element : UnitMoveList)
		{
			if (Element.Unit == unit)
			{
				//不做重复的添加
				return;
			}
		}
		FUnitMoveState MoveState;
		MoveState.Unit = unit;
		MoveState.Direction = GetDirectionIntForUnit(unit);
		MoveState.CurrentMoveTime = 0;
		float TotalDistance = SplineComponent->GetSplineLength();
		MoveState.MaxMoveTime = TotalDistance/unit->LinearSpeed;
		
		UnitMoveList.Add(MoveState);
	}
}

void ATrack::RemoveUnitFromTrack(AMovableUnits* unit)
{
	int32 i = 0;
	for (auto Element : UnitMoveList)
	{
		if (Element.Unit == unit)
		{
			UnitMoveList.RemoveAt(i);
			return;
		}
		i++;
	}
}

void ATrack::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (URMBlueprintFunctionLibrary::IsServer())
	{
		float TotalDistance = SplineComponent->GetSplineLength();
		for (auto MoveState : UnitMoveList)
		{
			//运动到头仍未被移除，按道理应该不会有这种情况
			if (MoveState.CurrentMoveTime>=MoveState.MaxMoveTime)
			{
				RemoveUnitFromTrack(MoveState.Unit);
			}
			MoveState.CurrentMoveTime = MoveState.CurrentMoveTime + DeltaSeconds;
			//移动路线上的unit
			float CurrentDistance = 0;
			if (MoveState.Direction == 1)
			{
				CurrentDistance = MoveState.CurrentMoveTime * MoveState.Unit->LinearSpeed;
			}
			if (MoveState.Direction == -1)
			{
				CurrentDistance = TotalDistance - MoveState.CurrentMoveTime * MoveState.Unit->LinearSpeed;
			}
			FVector CurrentLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistance,ESplineCoordinateSpace::World);
			FRotator CurrentRotation = SplineComponent->GetRotationAtDistanceAlongSpline(CurrentDistance,ESplineCoordinateSpace::World);
			// 设置物体位置
			MoveState.Unit->SetActorLocation(CurrentLocation);
			MoveState.Unit->SetActorRotation(CurrentRotation);
		}
	}	
}

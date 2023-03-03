// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"

#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"

ATrack::ATrack()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
}

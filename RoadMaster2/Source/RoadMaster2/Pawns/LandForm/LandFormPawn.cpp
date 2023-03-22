// Fill out your copyright notice in the Description page of Project Settings.


#include "LandFormPawn.h"
#include "RoadMaster2/Pawns/Units/MovableUnits.h"
#include "ShaderPrintParameters.h"

// Sets default values
ALandFormPawn::ALandFormPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UnitLauncher = CreateDefaultSubobject<UUnitLauncherComponent>(TEXT("UnitLauncher"));
	UnitLauncher->LandFormOwner = this;
	UnitLauncher->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALandFormPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALandFormPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALandFormPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ALandFormPawn::GetWayPoint()
{
	if (IsValid(WayPoint))
	{
		return WayPoint->GetActorPositionForRenderer();
	}
	return FVector::Zero();
}

ALandFormPawn* ALandFormPawn::GetTargetPointByInput(AMovableUnits* ComingUnit)
{
	if (ComingUnit)
	{
		ALandFormPawn* From = ComingUnit->GetStartLand();
		for (TMap<ALandFormPawn*, bool>::TConstIterator iter = NeighborMap.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Key != From && iter->Value != false)
			{
				return iter->Key;
			}
		}
		return From;
	}
	return nullptr;
}




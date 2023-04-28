// Fill out your copyright notice in the Description page of Project Settings.


#include "MinerFactory.h"

#include "EnhancedInputComponent.h"
#include "Components/SphereComponent.h"
#include "RoadMaster2/Component/UnitSpawnerComponent.h"
#include "RoadMaster2/Pawns/Units/MovableUnits.h"
#include "RoadMaster2/PlayerController/InGamePlayerControllerBase.h"

void AMinerFactory::BeginPlay()
{
	UnitSpawner = CreateDefaultSubobject<UUnitSpawnerComponent>(TEXT("UnitSpawner"));
	UnitSpawner->LandFormOwner = this;
	Collider->OnClicked.AddDynamic(this, &AMinerFactory::OnSelectStartPoint);
}

void AMinerFactory::SpawnUnit()
{
	UnitSpawner->SpawnUnit_Server();
}

void AMinerFactory::OnSelectStartPoint(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UWorld* World = GetWorld();
	if (World)
	{
		auto PC = static_cast<AInGamePlayerControllerBase*>(World->GetFirstPlayerController());
		if (PC->PlayerIndex == PlayerIndex)//是当前玩家 否则不能选中
		{
			PC->SelectFactory(this);
		}
	}
}

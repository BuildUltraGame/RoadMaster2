// Fill out your copyright notice in the Description page of Project Settings.


#include "Destination.h"

#include "GameFramework/GameStateBase.h"
#include "RoadMaster2/Data/UnitInfoBase.h"
#include "RoadMaster2/GameState/InBattleGameState.h"
#include "RoadMaster2/Pawns/Units/MovableUnits.h"
#include "RoadMaster2/Pawns/Units/TransportUnit.h"
#include "RoadMaster2/PlayerController/InGamePlayerControllerBase.h"
#include "RoadMaster2/PlayerState/InGamePlayerStateBase.h"

bool ADestination::ExecLandformEffect(AMovableUnits* Unit)
{
	//如果是运输单位
	if (Unit->IsA(ATransportUnit::StaticClass()))
	{
		if (Unit->PlayerIndex == PlayerIndex ||PlayerIndex == 0)
		{
			auto World = GWorld;
			auto InGameState = World->GetGameState<AInBattleGameState>();
			TArray<APlayerState*> PlayerStates = World->GetGameState()->PlayerArray;
			for (APlayerState* InPlayerState : PlayerStates)
			{
				auto InGamePlayerState = static_cast<AInGamePlayerStateBase*>(InPlayerState);
				auto InGamePlayerController = static_cast<AInGamePlayerControllerBase*>(InGamePlayerState->GetPlayerController());
				if (InGamePlayerController->PlayerGamePosIndex == Unit->PlayerIndex)
				{
					auto Info = InGameState->GetUnitInfoByID(Unit->UnitID);
					InGamePlayerState->GameScore = InGamePlayerState->GameScore + Info->Score;
					World->DestroyActor(Unit);
					return true;
				}
			}
		}
	}
	return Super::ExecLandformEffect(Unit);
}

void ADestination::BeginPlay()
{
	Super::BeginPlay();
	WorkAble = false;
}

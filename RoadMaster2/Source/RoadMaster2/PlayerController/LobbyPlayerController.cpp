// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"

#include "AdvancedSessionsLibrary.h"
#include "Net/UnrealNetwork.h"
#include "RoadMaster2/SubSystem/RMGameInstanceSubsystem.h"

void ALobbyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyPlayerController,GameMapID);
	DOREPLIFETIME(ALobbyPlayerController,RoomPlayerList);
}
//暂时没啥区别
void ALobbyPlayerController::OnRepRefreshRoom()
{
	SaveNetIDAndIndex();
	UpdateRoomUI();
}

void ALobbyPlayerController::OnGameMapIDChange()
{
	SaveNetIDAndIndex();
	UpdateRoomUI();
}

bool ALobbyPlayerController::IsSelfPlayerController(APlayerController* PC)
{
	UWorld* World = GetWorld();
	APlayerController* OwnPC = World->GetFirstPlayerController();
	return  OwnPC == PC;
}

void ALobbyPlayerController::SaveNetIDAndIndex()
{
	UWorld* World = GetWorld();	
	int32 OwnPlayerID = -1;
	APlayerController* OwnNativePC = World->GetFirstPlayerController();
	if (OwnNativePC->PlayerState)
	{
		OwnPlayerID = OwnNativePC->PlayerState->GetPlayerId();
	}
	for (TArray<FPlayerConnectInformation>::TConstIterator InformationIter = RoomPlayerList.CreateConstIterator(); InformationIter; ++InformationIter)
	{
		if (InformationIter)
		{
			auto PlayerID = InformationIter->PlayerId;
			if (PlayerID == OwnPlayerID)
			{
				UGameInstance* GameInstance = World->GetGameInstance();
				auto RMSys = GameInstance->GetSubsystem<URMGameInstanceSubsystem>();
				RMSys->CurrentInMapIndex = InformationIter->index;
			}		
		}
	}
}

void ALobbyPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	SaveNetIDAndIndex();
}

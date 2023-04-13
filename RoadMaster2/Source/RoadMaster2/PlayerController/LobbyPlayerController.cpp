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
	FString OwnPlayerName;
	APlayerController* OwnNativePC = World->GetFirstPlayerController();
	if (OwnNativePC->PlayerState)
	{
		OwnPlayerName = OwnNativePC->PlayerState->GetPlayerName();
	}
	ALobbyPlayerController* OwnPC = static_cast<ALobbyPlayerController*>(OwnNativePC);
	for (TArray<FPlayerConnectInformation>::TConstIterator InformationIter = RoomPlayerList.CreateConstIterator(); InformationIter; ++InformationIter)
	{
		if (InformationIter)
		{
			auto PlayerName = InformationIter->PlayerName.ToString();
			if (OwnPC->PlayerState)
			{
				OwnPlayerName = OwnPC->PlayerState->GetPlayerName();
				if (PlayerName == OwnPlayerName)
				{
					UGameInstance* GameInstance = World->GetGameInstance();
					auto RMSys = GameInstance->GetSubsystem<URMGameInstanceSubsystem>();
					RMSys->CurrentInMapIndex = InformationIter->index;
				}
			}			
		}
	}
}

void ALobbyPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	SaveNetIDAndIndex();
}

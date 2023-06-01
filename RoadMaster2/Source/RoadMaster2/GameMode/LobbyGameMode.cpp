// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "RoadMaster2/PlayerController/LobbyPlayerController.h"
#include "RoadMaster2/SubSystem/RMGameInstanceSubsystem.h"
#include "RoadMaster2/Tools/RMBlueprintFunctionLibrary.h"

ALobbyGameMode::ALobbyGameMode()
{
	
}

void ALobbyGameMode::RepRoomInformation(TArray<FPlayerConnectInformation> RoomList,int32 MapID)
{
	UWorld* World = GWorld;
	int32 index = 0;
	for (TArray<TWeakObjectPtr<APlayerController> >::TConstIterator PCIterator = World->GetPlayerControllerIterator(); PCIterator; ++PCIterator)
	{
		ALobbyPlayerController* PC = static_cast<ALobbyPlayerController*>(PCIterator->Get());
		
		if (IsValid(PC))
		{
			PC->RoomPlayerList = RoomList;
			PC->GameMapID = MapID;
			index++;
		}
	}
	//记录最大人数
	SaveServerMaxPlayer(index);
}


void ALobbyGameMode::SaveServerMaxPlayer(int32 MaxPlayers)
{
	//服务器储存人数
	if (URMBlueprintFunctionLibrary::IsServer())
	{
		UGameInstance* GameInstance = GWorld->GetGameInstance();
		auto RMSys = GameInstance->GetSubsystem<URMGameInstanceSubsystem>();
		RMSys->MaxPlayer = MaxPlayers;
	}
}


TArray<ALobbyPlayerController*> ALobbyGameMode::GetPlayerControllerList()
{
	UWorld* World = GWorld;
	TArray<ALobbyPlayerController*> PlayerList;
	
	for (TArray<TWeakObjectPtr<APlayerController> >::TConstIterator PCIterator = World->GetPlayerControllerIterator(); PCIterator; ++PCIterator)
	{
		APlayerController* PC = PCIterator->Get();
		
		if (PC&& PC->IsA<ALobbyPlayerController>()) 
		{
			PlayerList.Add(static_cast<ALobbyPlayerController*>(PC));
		}
	}
	return PlayerList;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

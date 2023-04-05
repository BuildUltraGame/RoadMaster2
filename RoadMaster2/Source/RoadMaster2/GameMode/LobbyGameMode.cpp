// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "RoadMaster2/PlayerController/LobbyPlayerController.h"

ALobbyGameMode::ALobbyGameMode()
{
	
}

void ALobbyGameMode::RepRoomInformation(TArray<FPlayerConnectInformation> RoomList,int32 MapID)
{
	UWorld* World = GetWorld();	
	for (TArray<TWeakObjectPtr<APlayerController> >::TConstIterator PCIterator = World->GetPlayerControllerIterator(); PCIterator; ++PCIterator)
	{
		ALobbyPlayerController* PC = static_cast<ALobbyPlayerController*>(PCIterator->Get());
		
		if (IsValid(PC))
		{
			PC->RoomPlayerList = RoomList;
			PC->GameMapID = MapID;
		}
	}
}


TArray<ALobbyPlayerController*> ALobbyGameMode::GetPlayerControllerList()
{
	UWorld* World = GetWorld();
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

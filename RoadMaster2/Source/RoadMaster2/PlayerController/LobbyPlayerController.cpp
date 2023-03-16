// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"

#include "Net/UnrealNetwork.h"

void ALobbyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyPlayerController,GameMapID);
	DOREPLIFETIME(ALobbyPlayerController,RoomPlayerList);
}
//暂时没啥区别
void ALobbyPlayerController::OnRepRefreshRoom()
{
	UpdateRoomUI();
}

void ALobbyPlayerController::OnGameMapIDChange()
{
	UpdateRoomUI();
}

bool ALobbyPlayerController::IsSelfPlayerController(APlayerController* PC)
{
	UWorld* World = GetWorld();
	APlayerController* OwnPC = World->GetFirstPlayerController();
	return  OwnPC == PC;
}

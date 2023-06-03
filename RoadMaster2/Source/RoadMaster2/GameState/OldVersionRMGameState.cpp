// Fill out your copyright notice in the Description page of Project Settings.


#include "OldVersionRMGameState.h"

#include "RoadMaster2/PlayerController/InGamePlayerControllerBase.h"

void AOldVersionRMGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AOldVersionRMGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AOldVersionRMGameState::InitSubStateArray()
{
	Super::InitSubStateArray();
}
//覆写的StartGamePlay，不调用基类的了
void AOldVersionRMGameState::StartGamePlay(EInGameSubState OldState)
{
	IsToEndGame = false;
	UGameInstance* GameInstance = GWorld->GetGameInstance();
	auto PlayerController = static_cast<AInGamePlayerControllerBase*>(GameInstance->GetFirstLocalPlayerController());
	if (IsValid(PlayerController))
	{
		PlayerController->OpenBattleHUD();
	}
}

bool AOldVersionRMGameState::CheckGamePlay()
{
	return Super::CheckGamePlay();
}

void AOldVersionRMGameState::EndGamePlay(bool IsTimeOut)
{
	Super::EndGamePlay(IsTimeOut);
}

bool AOldVersionRMGameState::CheckPreArrangement()
{
	return true;
}

EInGameSubState AOldVersionRMGameState::GetNextState(EInGameSubState CurState)
{
	return Super::GetNextState(CurState);
}

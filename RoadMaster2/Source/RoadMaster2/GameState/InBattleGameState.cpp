// Fill out your copyright notice in the Description page of Project Settings.


#include "InBattleGameState.h"

#include "Net/UnrealNetwork.h"

void AInBattleGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AInBattleGameState, InGameSubState);
}

void AInBattleGameState::OnRep_InGameSubState(EInGameSubState OldValue)
{
	//todo Here 游戏状态转移的接口方法
	if (InGameSubState == EInGameSubState::GamePlay)
	{
		OnGameStartedDelegate.Execute(OldValue);
	}
}

void AInBattleGameState::BeginPlay()
{
	Super::BeginPlay();
	OnGameStartedDelegate.BindUFunction(this,TEXT("GamePlayStart"));
	InGameSubState = EInGameSubState::WaitingForConnect;
}

void AInBattleGameState::GamePlayStart(EInGameSubState OldState)
{
	
}

void AInBattleGameState::SetInGameSubState(EInGameSubState NewState)
{
	if (GIsServer)
	{
		InGameSubState = NewState;
	}
}

void AInBattleGameState::ReportConnectionInServer_Implementation()
{
	
}


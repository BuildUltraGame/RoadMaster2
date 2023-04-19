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
	ExecSubStateChange(OldValue);
}

void AInBattleGameState::ExecSubStateChange(EInGameSubState OldValue)
{
	//todo Here 游戏状态转移的接口方法
	if (InGameSubState == EInGameSubState::Initializing)
	{
		DoInitialize();
	}
	if (InGameSubState == EInGameSubState::GamePlay)
	{
		OnGameStartedDelegate.Execute(OldValue);
	}
}

void AInBattleGameState::InBattleGameState()
{
	InGameSubState = EInGameSubState::WaitingForConnect;
}

void AInBattleGameState::BeginPlay()
{
	Super::BeginPlay();
	OnGameStartedDelegate.BindUFunction(this,TEXT("GamePlayStart"));
	// todo: 这里可以加入一个超时的逻辑，超时了可以直接转换到下一个阶段
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

void AInBattleGameState::DoInitialize()
{
	
}

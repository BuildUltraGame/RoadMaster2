// Fill out your copyright notice in the Description page of Project Settings.


#include "InBattleGameState.h"

#include "Net/UnrealNetwork.h"
#include "RoadMaster2/Data/UnitInfoBase.h"
#include "RoadMaster2/GameMode/InGameGameModeBase.h"
#include "RoadMaster2/PlayerState/InGamePlayerStateBase.h"

#pragma region base function

void AInBattleGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInBattleGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AInBattleGameState, InGameSubState);
}


AInBattleGameState::AInBattleGameState()
{	
	InGameSubState = EInGameSubState::WaitingForConnect;
	IsToEndGame = false;
	InitSubStateArray();
	//初始化各个阶段的时间
	for (const auto& SubState : SubStateMap)
	{		
		if (!TimePerState.Contains(SubState.Value.SubState))
		{
			TimePerState.Add(SubState.Value.SubState,0);			
		}
	}
}

void AInBattleGameState::BeginPlay()
{
	Super::BeginPlay();
	StateTimeOutTimerStart();
}

#pragma endregion

#pragma region <<<<<state controller


void AInBattleGameState::SetInGameSubState(EInGameSubState NewState)
{
	if (GIsServer)
	{
		if (InGameSubState != NewState)
		{			
			InGameSubState = NewState;
		}
	}
}

void AInBattleGameState::OnRep_InGameSubState(EInGameSubState OldValue)
{
	ExecSubStateChange(OldValue);
}

//状态进入的起点
void AInBattleGameState::ExecSubStateChange(EInGameSubState OldValue)
{
	const auto StateStruct = SubStateMap[InGameSubState];
	if (StateStruct.StateStartDelegate.IsBound())
	{
		StateStruct.StateStartDelegate.Execute(OldValue);
	}
	//服务器进行倒计时计算
	StateTimeOutTimerStart();
	UE_LOG(LogTemp, Display, TEXT("ExecSubStateChange --- %d"), StateStruct.SubState);
}


//阶段倒计时结束
void AInBattleGameState::SubStateTimeOut()
{
	if (GIsServer)
	{
		//执行最后的操作
		const auto StateStruct = SubStateMap[InGameSubState];
		if (StateStruct.StateEndDelegate.IsBound())
		{
			StateStruct.StateEndDelegate.Execute(true);
		}
		//切换状态
		SetInGameSubState(StateStruct.GetNextStateDelegate.Execute(StateStruct.SubState));
	}	
}

//超时计时器启动
void AInBattleGameState::StateTimeOutTimerStart()
{
	if (GIsServer)
	{
		if (TimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		if (TimePerState[InGameSubState] > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AInBattleGameState::SubStateTimeOut, TimePerState[InGameSubState], false, 0);
		}
	}
}

// 定时check当前阶段是否完成
void AInBattleGameState::CheckCurrentStateChange()
{
	if (GIsServer)
	{
		//执行最后的操作
		const auto StateStruct = SubStateMap[InGameSubState];
		if (StateStruct.CheckStateEndDelegate.IsBound())
		{
			if (StateStruct.CheckStateEndDelegate.Execute())
			{			
				//切换状态
				if (StateStruct.StateEndDelegate.IsBound())
				{
					StateStruct.StateEndDelegate.Execute(false);
				}
				SetInGameSubState(StateStruct.GetNextStateDelegate.Execute(StateStruct.SubState));
			}
		}
	}	
}

#pragma endregion state controller>>>>>


#pragma  region  <<<Delegates For State Changing
void AInBattleGameState::StartConnect(EInGameSubState OldState)
{
}

bool AInBattleGameState::CheckConnect()
{
	if (GIsServer)
	{
		auto GameModeInstance = GetDefaultGameMode<AInGameGameModeBase>();
		if (GameModeInstance->NumTravellingPlayers == 0)
		{
			return true;
		}
	}
	return false;
}

void AInBattleGameState::EndConnect(bool IsTimeOut)
{
}

void AInBattleGameState::StartInitialize(EInGameSubState OldState)
{
	if (!UnitClassArray.IsEmpty())
	{
		//GameState初始化
		UWorld* World = GetWorld();
		for (auto Element : UnitClassArray)
		{
			//复制CDO,覆盖配置,加入信息数组
			auto SubObj = World->SpawnActor<AUnitInfoBase>(Element);
			SubObj->DoDataOverride();
			UnitInfos.Add(SubObj);
		}
		//PlayerState初始化
		const auto OwnPC = World->GetFirstPlayerController();
		const auto OwnPlayerState = static_cast<AInGamePlayerStateBase*>(OwnPC->PlayerState);
		if (IsValid(OwnPlayerState))
		{
			OwnPlayerState->InitialPlayerState();
		}
	}
}

bool AInBattleGameState::CheckInitialize()
{
	if (GIsServer)
	{
		for (auto PlayerState : PlayerArray)
		{
			const auto InGamePlayerState = static_cast<AInGamePlayerStateBase*>(PlayerState);
			if (!InGamePlayerState->IsPlayerStateInit)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void AInBattleGameState::EndInitialize(bool IsTimeOut)
{
}

void AInBattleGameState::StartPreArrangement(EInGameSubState OldState)
{
}

bool AInBattleGameState::CheckPreArrangement()
{
	return false;
}

void AInBattleGameState::EndPreArrangement(bool IsTimeOut)
{
}

void AInBattleGameState::StartGamePlay(EInGameSubState OldState)
{
}

bool AInBattleGameState::CheckGamePlay()
{
	return false;
}

void AInBattleGameState::EndGamePlay(bool IsTimeOut)
{
}

EInGameSubState AInBattleGameState::GetNextState(EInGameSubState CurState)
{
	switch (CurState)
	{
	case EInGameSubState::WaitingForConnect:
			return EInGameSubState::Initializing;
	case EInGameSubState::Initializing:
		return EInGameSubState::PreArrangement;
	case EInGameSubState::PreArrangement:
		return EInGameSubState::GamePlay;
	case EInGameSubState::GamePlay:
		if (IsToEndGame)
		{
			return EInGameSubState::End;
		}
		return EInGameSubState::BetweenGameSuspend;
	case EInGameSubState::BetweenGameSuspend:
		return EInGameSubState::GamePlay;
	default:
		return EInGameSubState::End;
	}	
}

#pragma endregion Delegates For State Changing>>>



void AInBattleGameState::InitSubStateArray()
{
	for (const auto& EnumValue : TEnumRange<EInGameSubState>())
	{
		FSubStateWithDelegate StateStruct;
		switch (EnumValue)
		{
		case EInGameSubState::WaitingForConnect:
			StateStruct.StateStartDelegate.BindUFunction(this,TEXT("StartConnect"));
			StateStruct.CheckStateEndDelegate.BindUFunction(this,TEXT("CheckConnect"));
			StateStruct.StateEndDelegate.BindUFunction(this,TEXT("EndConnect"));
			StateStruct.GetNextStateDelegate.BindUFunction(this,TEXT("GetNextState"));
			break;

		case EInGameSubState::Initializing:
			StateStruct.StateStartDelegate.BindUFunction(this,TEXT("StartInitialize"));
			StateStruct.CheckStateEndDelegate.BindUFunction(this,TEXT("CheckInitialize"));
			StateStruct.StateEndDelegate.BindUFunction(this,TEXT("EndInitialize"));
			StateStruct.GetNextStateDelegate.BindUFunction(this,TEXT("GetNextState"));
			break;

		case EInGameSubState::PreArrangement:
			StateStruct.StateStartDelegate.BindUFunction(this,TEXT("StartPreArrangement"));
			StateStruct.CheckStateEndDelegate.BindUFunction(this,TEXT("CheckPreArrangement"));
			StateStruct.StateEndDelegate.BindUFunction(this,TEXT("EndPreArrangement"));
			StateStruct.GetNextStateDelegate.BindUFunction(this,TEXT("GetNextState"));
			break;

		case EInGameSubState::GamePlay:
			StateStruct.StateStartDelegate.BindUFunction(this,TEXT("StartGamePlay"));
			StateStruct.CheckStateEndDelegate.BindUFunction(this,TEXT("CheckGamePlay"));
			StateStruct.StateEndDelegate.BindUFunction(this,TEXT("EndGamePlay"));
			StateStruct.GetNextStateDelegate.BindUFunction(this,TEXT("GetNextState"));
			break;

		case EInGameSubState::BetweenGameSuspend:
			StateStruct.GetNextStateDelegate.BindUFunction(this,TEXT("GetNextState"));
			break;

		case EInGameSubState::Settlement:
			StateStruct.GetNextStateDelegate.BindUFunction(this,TEXT("GetNextState"));
			break;

		default:
			// 处理未知枚举值
			break;
		}
		StateStruct.SubState = EnumValue;
		SubStateMap.Add(EnumValue,StateStruct);
	}
}

AUnitInfoBase* AInBattleGameState::GetUnitInfoByID(int32 UnitID)
{
	
}

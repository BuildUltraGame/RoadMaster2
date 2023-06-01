// Fill out your copyright notice in the Description page of Project Settings.


#include "InBattleGameState.h"

#include "Net/UnrealNetwork.h"
#include "RoadMaster2/Data/UnitInfoBase.h"
#include "RoadMaster2/GameMode/InGameGameModeBase.h"
#include "RoadMaster2/PlayerController/InGamePlayerControllerBase.h"
#include "RoadMaster2/PlayerState/InGamePlayerStateBase.h"
#include "RoadMaster2/SubSystem/RMGameInstanceSubsystem.h"
#include "RoadMaster2/Tools/RMBlueprintFunctionLibrary.h"

#pragma region base function

void AInBattleGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckCurrentStateChange();
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
	StateReportedPlayerAmount = 0;
	//初始化各个阶段的时间
	for (const auto& SubState : SubStateMap)
	{		
		if (!TimePerState.Contains(SubState.Value.SubState))
		{
			TimePerState.Add(SubState.Value.SubState,0);			
		}
	}
	SetActorTickEnabled(true);
}

void AInBattleGameState::BeginPlay()
{
	Super::BeginPlay();
	MinNetUpdateFrequency = 0.001f;
}

#pragma endregion

#pragma region <<<<<state controller


void AInBattleGameState::SetInGameSubState(EInGameSubState NewState)
{
	if (URMBlueprintFunctionLibrary::IsServer())
	{
		UE_LOG(LogTemp, Display, TEXT("SetInGameSubState Server--- %d"), NewState);
		if (InGameSubState != NewState)
		{			
			auto OldValue = InGameSubState;
			InGameSubState = NewState;
			StateReportedPlayerAmount = 0;
			ExecSubStateChange(OldValue);
		}
	}
}

void AInBattleGameState::OnRep_InGameSubState(EInGameSubState OldValue)
{
	UE_LOG(LogTemp, Display, TEXT("SetInGameSubState Client--- %d"), InGameSubState);
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
	//此处绕道使用playercontroller，是因为gamestate的所有权是server，而client无权调用gamestate的server RPC
	UGameInstance* GameInstance = GWorld->GetGameInstance();
	AInGamePlayerControllerBase* PC = static_cast<AInGamePlayerControllerBase*>(GameInstance->GetFirstLocalPlayerController());
	if (IsValid(PC))
	{
		PC->ReportSubStateSetSuccess();
	}
	if(URMBlueprintFunctionLibrary::IsServer())
	{		
		UE_LOG(LogTemp, Display, TEXT("ExecSubStateChange Server --- %d"), StateStruct.SubState);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("ExecSubStateChange Client --- %d"), StateStruct.SubState);
	}
	//服务器进行倒计时计算
	StateTimeOutTimerStart();
}

void AInBattleGameState::SubStateSetSuccess()
{
	StateReportedPlayerAmount++;
}

//阶段倒计时结束
void AInBattleGameState::SubStateTimeOut()
{
	if (URMBlueprintFunctionLibrary::IsServer())
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

//超时计时器启动 当时间配置为0的时候不启动计时，当时间配置小于0的时候跳过该阶段
void AInBattleGameState::StateTimeOutTimerStart()
{
	if (URMBlueprintFunctionLibrary::IsServer())
	{
		if (TimerHandle.IsValid())
		{
			GWorld->GetTimerManager().ClearTimer(TimerHandle);
		}
		if (TimePerState[InGameSubState] > 0)
		{
			GWorld->GetTimerManager().SetTimer(TimerHandle, this, &AInBattleGameState::SubStateTimeOut, TimePerState[InGameSubState], false, TimePerState[InGameSubState]);
		}	
	}
}

// 定时check当前阶段是否完成
void AInBattleGameState::CheckCurrentStateChange()
{
	if (URMBlueprintFunctionLibrary::IsServer())
	{
		//执行最后的操作
		const auto StateStruct = SubStateMap[InGameSubState];
		if (StateStruct.CheckStateEndDelegate.IsBound())
		{
			UGameInstance* GameInstance = GWorld->GetGameInstance();
			auto RMSys = GameInstance->GetSubsystem<URMGameInstanceSubsystem>();
			if (StateStruct.CheckStateEndDelegate.Execute()&&(RMSys->MaxPlayer == StateReportedPlayerAmount||InGameSubState == EInGameSubState::WaitingForConnect))
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
	if (URMBlueprintFunctionLibrary::IsServer())
	{
		UWorld* World = GWorld;
		auto GameModeInstance = World->GetAuthGameMode();
		auto InGameModeInstance = static_cast<AInGameGameModeBase*>(GameModeInstance);
		if (IsValid(InGameModeInstance))
		{
			UGameInstance* GameInstance = GWorld->GetGameInstance();
			auto RMSys = GameInstance->GetSubsystem<URMGameInstanceSubsystem>();
			if (InGameModeInstance->NumPlayers == RMSys->MaxPlayer)
			{
				return true;
			}
		}		
	}
	return false;
}

void AInBattleGameState::EndConnect(bool IsTimeOut)
{
	StateTimeOutTimerStart();
}

void AInBattleGameState::StartInitialize(EInGameSubState OldState)
{
	if (!UnitClassArray.IsEmpty())
	{
		//GameState初始化
		UWorld* World = GWorld;
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
	if (URMBlueprintFunctionLibrary::IsServer())
	{
		if (PlayerArray.IsEmpty())
		{
			return false;
		}
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
	for (auto Info : UnitInfos)
	{
		if (Info->UnitID == UnitID)
		{
			return Info;
		}
	}
	return nullptr;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "InBattleGameState.h"

#include "Net/UnrealNetwork.h"
#include "RoadMaster2/Data/UnitInfoBase.h"

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


void AInBattleGameState::InBattleGameState()
{
	InGameSubState = EInGameSubState::WaitingForConnect;
	//初始化各个阶段的时间
	TimePerState[EInGameSubState::WaitingForConnect] = 0;
	TimePerState[EInGameSubState::Initializing] = 0;
	TimePerState[EInGameSubState::PreArrangement] = 0;
	TimePerState[EInGameSubState::GamePlay] = 0;
	TimePerState[EInGameSubState::BetweenGameSuspend] = 0;
	TimePerState[EInGameSubState::Settlement] = 0;
}

void AInBattleGameState::BeginPlay()
{
	Super::BeginPlay();
	OnGameStartedDelegate.BindUFunction(this,TEXT("GamePlayStart"));
	CheckStateTimerStart();
}

#pragma endregion

#pragma region state controller


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
	//todo Here 游戏状态转移的接口方法
	if (InGameSubState == EInGameSubState::Initializing)
	{
		DoInitialize();
	}
	if (InGameSubState == EInGameSubState::GamePlay)
	{
		OnGameStartedDelegate.Execute(OldValue);
	}
	//服务器进行倒计时计算
	CheckStateTimerStart();
}


//阶段倒计时结束
void AInBattleGameState::SubStateTimeOut()
{
	if (InGameSubState == EInGameSubState::WaitingForConnect)
	{
		SetInGameSubState(EInGameSubState::Initializing);
	}
	
	if (InGameSubState == EInGameSubState::Initializing)
	{
		SetInGameSubState(EInGameSubState::PreArrangement);
	}
	
	if (InGameSubState == EInGameSubState::PreArrangement)
	{
		FinishPreArrageMent();
	}
	
	if (InGameSubState == EInGameSubState::GamePlay)
	{
		CheckGameEnd();
	}
}

void AInBattleGameState::CheckStateTimerStart()
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

#pragma endregion 


void AInBattleGameState::DoInitialize()
{
	if (!UnitClassArray.IsEmpty())
	{
		UWorld* World = GetWorld();
		for (auto Element : UnitClassArray)
		{
			//复制CDO,覆盖配置,加入信息数组
			auto SubObj = World->SpawnActor<AUnitInfoBase>(Element);
			SubObj->DoDataOverride();
			UnitInfos.Add(SubObj);
		}
	}
}

void AInBattleGameState::GamePlayStart(EInGameSubState OldState)
{
	
}


void AInBattleGameState::ReportConnectionInServer_Implementation()
{
	
}

void AInBattleGameState::FinishPreArrageMent()
{
}

void AInBattleGameState::CheckGameEnd()
{
}

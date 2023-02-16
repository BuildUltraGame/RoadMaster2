// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "InBattleGameState.generated.h"

UENUM()
enum class EInGameSubState : uint8
{
	/*  在同步上之前，等待连接的状态  */
	WaitingForConnect,
	/*  初始化的状态  */
	Initializing,
	/*  策略预选阶段  */
	PreArrangement,
	/*  游戏进行中	*/
	GamePlay,
	/*  暂停状态		*/
	Suspend,
	/*	节间暂停		*/
	BetweenGameSuspend,
	/*	结算阶段		*/
	Settlement,
	/*	结束阶段		*/
	End,
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGameStarted,EInGameSubState,OldState);


/**
 * 
 */
UCLASS()
class ROADMASTER2_API AInBattleGameState : public AGameState
{
	GENERATED_BODY()
public:
	UPROPERTY(ReplicatedUsing = OnRep_InGameSubState,BlueprintReadWrite)
	EInGameSubState InGameSubState;

	UFUNCTION()
	void OnRep_InGameSubState(EInGameSubState OldValue);

	UPROPERTY(BlueprintReadWrite)
	FOnGameStarted OnGameStartedDelegate;

	UFUNCTION()
	void GamePlayStart(EInGameSubState OldState);

	UFUNCTION(BlueprintCallable)
	void SetInGameSubState(EInGameSubState NewState);

	//汇报联机状态，用以确认联机数量
	UFUNCTION(Server,BlueprintCallable,Reliable)
	void ReportConnectionInServer();

	//初始化阶段的操作
	UFUNCTION()
	void DoInitialize();

	//
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const override;

	virtual void BeginPlay() override;
};

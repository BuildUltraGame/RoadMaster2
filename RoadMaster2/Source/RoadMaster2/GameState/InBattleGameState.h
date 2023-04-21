// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "InBattleGameState.generated.h"

class AUnitInfoBase;
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

	//执行阶段转换时的主要方法
	UFUNCTION()
	void ExecSubStateChange(EInGameSubState OldValue);

	UPROPERTY(BlueprintReadWrite)
	FOnGameStarted OnGameStartedDelegate;

	UFUNCTION()
	void GamePlayStart(EInGameSubState OldState);

	UFUNCTION(BlueprintCallable)
	void SetInGameSubState(EInGameSubState NewState);

	//汇报联机状态，用以确认联机数量 todo 目前没啥用
	UFUNCTION(Server,BlueprintCallable,Reliable)
	void ReportConnectionInServer();

	//初始化阶段的操作
	UFUNCTION()
	void DoInitialize();

	

#pragma region >>> Game Base Variables

	//用以配置当前关卡出场单位
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TSubclassOf<AUnitInfoBase>> UnitClassArray;

	//运行时，储存单位模板信息
	UPROPERTY(BlueprintReadWrite)
	TArray<AUnitInfoBase*> UnitInfos;

	//每个阶段的游戏时间
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TMap<EInGameSubState,int> TimePerState;

#pragma endregion <<< Game Base Variables

	//阶段计时器handle
	FTimerHandle TimerHandle;
	
	void InBattleGameState();

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	//倒计时结束的操作
	virtual void SubStateTimeOut();

	//预选阶段结束的接口
	virtual void FinishPreArrageMent();

	//每段游戏结束的接口
	virtual void CheckGameEnd();

private:
	void CheckStateTimerStart();
};

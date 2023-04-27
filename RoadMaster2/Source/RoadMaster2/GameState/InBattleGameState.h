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
	WaitingForConnect UMETA(DisplayName = "WaitingForConnect"),
	/*  初始化的状态  */
	Initializing UMETA(DisplayName = "Initializing"),
	/*  策略预选阶段  */
	PreArrangement UMETA(DisplayName = "PreArrangement"),
	/*  游戏进行中	*/
	GamePlay UMETA(DisplayName = "GamePlay"),
	/*  暂停状态		*/
	Suspend UMETA(DisplayName = "Suspend"),
	/*	节间暂停		*/
	BetweenGameSuspend UMETA(DisplayName = "BetweenGameSuspend"),
	/*	结算阶段		*/
	Settlement UMETA(DisplayName = "Settlement"),
	/*	结束阶段		*/
	End UMETA(DisplayName = "End"),
};

ENUM_RANGE_BY_COUNT(EInGameSubState, EInGameSubState::End);

//阶段开始时的委托
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnStateStartDelegate,EInGameSubState,OldState);

//判断阶段结束的委托
DECLARE_DYNAMIC_DELEGATE_RetVal(bool,FCheckStateEndDelegate);

//阶段结束时的委托
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnStateEndDelegate,bool,IsTimeOut);

//获取下一阶段的委托
DECLARE_DELEGATE_RetVal_OneParam(EInGameSubState,FGetNextStateDelegate,EInGameSubState)

USTRUCT()
struct FSubStateWithDelegate
{
	GENERATED_BODY()

	UPROPERTY()
	EInGameSubState SubState;

	UPROPERTY()
	FOnStateStartDelegate StateStartDelegate;

	//注意 这里不能被uproperty修饰，因为没有size
	FCheckStateEndDelegate CheckStateEndDelegate;

	UPROPERTY()
	FOnStateEndDelegate StateEndDelegate;

	FGetNextStateDelegate GetNextStateDelegate;
};



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

	//检查当前状态的切换
	UFUNCTION()
	void CheckCurrentStateChange();
	
	UFUNCTION()
	void OnRep_InGameSubState(EInGameSubState OldValue);

	//执行阶段转换时的主要方法
	UFUNCTION()
	void ExecSubStateChange(EInGameSubState OldValue);

	UFUNCTION(BlueprintCallable)
	void SetInGameSubState(EInGameSubState NewState);	

	//每个状态的进入和判定函数
	UPROPERTY()
	TMap<EInGameSubState,FSubStateWithDelegate> SubStateMap;
	

#pragma region >>> Game Base Variables //Check 方法只在服务器执行，start和end方法在每一个端执行

	//用以配置当前关卡出场单位
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TSubclassOf<AUnitInfoBase>> UnitClassArray;

	//运行时，储存单位模板信息
	UPROPERTY(BlueprintReadWrite)
	TArray<AUnitInfoBase*> UnitInfos;

	//每个阶段的游戏时间
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TMap<EInGameSubState,int> TimePerState;

	//开局金钱
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 StartFund;

	UPROPERTY(BlueprintReadWrite)
	bool IsToEndGame;

#pragma endregion <<< Game Base Variables

	//阶段计时器handle
	FTimerHandle TimerHandle;
	
	AInBattleGameState();

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	//倒计时结束的操作
	virtual void SubStateTimeOut();
	
	//记录了各个SubState的arr，包括其检查方式和回调
	virtual void InitSubStateArray();

#pragma region <<<Delegates For State Changing

	//连接阶段的操作
	UFUNCTION()
	virtual void StartConnect(EInGameSubState OldState);

	UFUNCTION()
	virtual bool CheckConnect();
	
	UFUNCTION()
	virtual void EndConnect(bool IsTimeOut);

	//初始化阶段的操作
	UFUNCTION()
	virtual void StartInitialize(EInGameSubState OldState);

	UFUNCTION()
	virtual bool CheckInitialize();
	
	UFUNCTION()
	virtual void EndInitialize(bool IsTimeOut);

	//预选阶段的操作
	UFUNCTION()
	virtual void StartPreArrangement(EInGameSubState OldState);

	UFUNCTION()
	virtual bool CheckPreArrangement();
	
	UFUNCTION()
	virtual void EndPreArrangement(bool IsTimeOut);

	//预选阶段的操作
	UFUNCTION()
	virtual void StartGamePlay(EInGameSubState OldState);

	UFUNCTION()
	virtual bool CheckGamePlay();
	
	UFUNCTION()
	virtual void EndGamePlay(bool IsTimeOut);

	UFUNCTION()
	virtual EInGameSubState GetNextState(EInGameSubState CurState);

#pragma endregion Delegates For State Changing>>>


private:
	void StateTimeOutTimerStart();
};

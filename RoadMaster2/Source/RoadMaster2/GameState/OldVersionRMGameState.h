// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InBattleGameState.h"
#include "OldVersionRMGameState.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API AOldVersionRMGameState : public AInBattleGameState
{
	GENERATED_BODY()

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void InitSubStateArray() override;
	virtual void StartGamePlay(EInGameSubState OldState) override;
	virtual bool CheckGamePlay() override;
	virtual void EndGamePlay(bool IsTimeOut) override;
	virtual EInGameSubState GetNextState(EInGameSubState CurState) override;	
};

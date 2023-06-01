// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "InGamePlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API AInGamePlayerStateBase : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnRep_PlayerId() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//player state 在 Initial阶段的初始化，完成后认为该client初始化完成
	virtual void InitialPlayerState();

#pragma region Client Player State Variables


#pragma  endregion Client Player State Variables


#pragma region >>> Game Base Variables
	//当局得分
	UPROPERTY(BlueprintReadWrite,ReplicatedUsing = OnRep_RoundScore)
	int32 RoundScore;
	//游戏得分
	UPROPERTY(BlueprintReadWrite,ReplicatedUsing = OnRep_GameScore)
	int32 GameScore;
	//资金
	UPROPERTY(BlueprintReadWrite,ReplicatedUsing = OnRep_Fund)
	int32 Fund;

	UFUNCTION()
	void OnRep_RoundScore();

	UFUNCTION()
	void OnRep_GameScore();

	UFUNCTION()
	void OnRep_Fund();


#pragma endregion <<< Game Base Variables

	
private:
	
};

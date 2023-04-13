// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FPlayerConnectInformation
{
	GENERATED_BODY()
	//玩家名字
	UPROPERTY(BlueprintReadWrite)
	FName PlayerName;
	//延迟
	UPROPERTY(BlueprintReadWrite)
	int32 Ping;
	//玩家是否是房主
	UPROPERTY(BlueprintReadWrite)
	bool IsOwner;
	//编号
	UPROPERTY(BlueprintReadWrite)
	int32 index;
};


UCLASS()
class ROADMASTER2_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool IsBusyBoxShowing = false;

	UPROPERTY(ReplicatedUsing = OnRepRefreshRoom,BlueprintReadWrite)
	TArray<FPlayerConnectInformation> RoomPlayerList;

	UPROPERTY(ReplicatedUsing = OnGameMapIDChange,BlueprintReadWrite)
	int32 GameMapID;

	UPROPERTY(BlueprintReadWrite)
	int32 PlayerIndex;

	UFUNCTION()
	void OnRepRefreshRoom();

	UFUNCTION()
	void OnGameMapIDChange();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateRoomUI();

	UFUNCTION(BlueprintCallable)
	bool IsSelfPlayerController(APlayerController* PC);

	UFUNCTION(BlueprintCallable)
	void SaveNetIDAndIndex();

	/** PlayerState Replication Notification Callback */
	virtual void OnRep_PlayerState() override;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const override;
};

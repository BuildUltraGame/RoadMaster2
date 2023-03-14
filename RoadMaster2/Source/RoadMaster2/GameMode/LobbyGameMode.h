// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

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


/**
 * 
 */
UCLASS()
class ROADMASTER2_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ALobbyGameMode();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 CurrentMapID;

	UFUNCTION(BlueprintCallable)
	void RepRoomInformation(TArray<FPlayerConnectInformation> RoomList,int32 MapID);

	UFUNCTION(BlueprintCallable)
	TArray<ALobbyPlayerController*> GetPlayerControllerList();
	
};

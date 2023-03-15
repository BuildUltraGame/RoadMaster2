// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"



struct FPlayerConnectInformation;


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

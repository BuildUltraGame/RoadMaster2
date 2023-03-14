// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */


struct FPlayerConnectInformation;


UCLASS()
class ROADMASTER2_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	bool IsBusyBoxShowing = false;

	UPROPERTY(ReplicatedUsing = OnRepRefreshRoom,BlueprintReadWrite)
	TArray<struct FPlayerConnectInformation> RoomPlayerList;

	UPROPERTY(ReplicatedUsing = OnGameMapIDChange,BlueprintReadWrite)
	int32 GameMapID;

	UFUNCTION()
	void OnRepRefreshRoom();

	UFUNCTION()
	void OnGameMapIDChange();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateRoomUI();

	
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const override;
};

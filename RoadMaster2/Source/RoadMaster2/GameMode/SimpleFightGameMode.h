// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleFightGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API ASimpleFightGameMode : public AGameMode
{
	GENERATED_BODY()
	#pragma region    >>> Override Functions
public:
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual APlayerController* PreCreatePlayerController(uint32 PlayerKey);

	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	
	virtual APlayerController* Login(class UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	virtual void Logout(AController* Exiting) override;

	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

	virtual void RestartPlayerAtTransform(AController* NewPlayer, const FTransform& SpawnTransform);

	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;

	virtual bool AllowCheats(APlayerController* P) override;

	virtual void UpdateGameplayMuteList(APlayerController* aPlayer) override;

	virtual bool MustSpectate_Implementation(APlayerController* NewPlayerController) const override;

	uint32 GenerateUniqueKeyEditor();
	
	TSet<uint32> EditorPlayerKeySet;

#pragma endregion <<< Override Functions 


};

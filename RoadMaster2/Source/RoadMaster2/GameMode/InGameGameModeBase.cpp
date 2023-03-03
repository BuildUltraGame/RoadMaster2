// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameGameModeBase.h"

void AInGameGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AInGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AInGameGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


APlayerController* AInGameGameModeBase::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	return Super::SpawnPlayerController(InRemoteRole, Options);
}

void AInGameGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* AInGameGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AInGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AInGameGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AInGameGameModeBase::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
}

void AInGameGameModeBase::RestartPlayerAtTransform(AController* NewPlayer, const FTransform& SpawnTransform)
{
	Super::RestartPlayerAtTransform(NewPlayer, SpawnTransform);
}

void AInGameGameModeBase::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);
}

bool AInGameGameModeBase::AllowCheats(APlayerController* P)
{
	return Super::AllowCheats(P);
}

void AInGameGameModeBase::UpdateGameplayMuteList(APlayerController* aPlayer)
{
	Super::UpdateGameplayMuteList(aPlayer);
}

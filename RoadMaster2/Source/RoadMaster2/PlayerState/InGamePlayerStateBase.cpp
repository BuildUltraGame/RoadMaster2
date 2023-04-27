// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerStateBase.h"

#include "Net/UnrealNetwork.h"
#include "RoadMaster2/PlayerController/InGamePlayerControllerBase.h"

void AInGamePlayerStateBase::BeginPlay()
{
	Super::BeginPlay();
	IsPlayerStateInit = false;
}

void AInGamePlayerStateBase::OnRep_PlayerId()
{
	Super::OnRep_PlayerId();
}

void AInGamePlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AInGamePlayerStateBase, RoundScore);
	DOREPLIFETIME(AInGamePlayerStateBase, GameScore);
	DOREPLIFETIME(AInGamePlayerStateBase, Fund);
	DOREPLIFETIME(AInGamePlayerStateBase, IsPlayerStateInit);
}

void AInGamePlayerStateBase::OnRep_RoundScore()
{
}

void AInGamePlayerStateBase::OnRep_GameScore()
{
}

void AInGamePlayerStateBase::OnRep_Fund()
{
}

void AInGamePlayerStateBase::InitialPlayerState()
{
	auto PC = static_cast<AInGamePlayerControllerBase*>(GetPlayerController());
	if (IsValid(PC))
	{
		PC->SetPlayerStartPoint();
	}
	IsPlayerStateInit = true;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "RMBlueprintFunctionLibrary.h"

void URMBlueprintFunctionLibrary::ShowLogInBlueprint(FString logs)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *logs);
}

void URMBlueprintFunctionLibrary::GetMapConfigByMapID(int32 MapID)
{
	
}

bool URMBlueprintFunctionLibrary::IsServer()
{
	//GIsServer数值不准确！当在editor内的时候他总是为true
	auto NetMode = GWorld->GetNetMode();
	if (NetMode != NM_Client)
	{
		return true;
	}
	return false;
}

APlayerController* URMBlueprintFunctionLibrary::GetLocalPlayerController()
{
	auto GameInstance = GWorld->GetGameInstance();
	if (IsValid(GameInstance))
	{
		return GameInstance->GetFirstLocalPlayerController();
	}
	return nullptr;
}

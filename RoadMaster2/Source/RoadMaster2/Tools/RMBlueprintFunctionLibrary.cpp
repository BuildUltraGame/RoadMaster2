// Fill out your copyright notice in the Description page of Project Settings.


#include "RMBlueprintFunctionLibrary.h"

void URMBlueprintFunctionLibrary::ShowLogInBlueprint(FString logs)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *logs);
}

void URMBlueprintFunctionLibrary::GetMapConfigByMapID(int32 MapID)
{
	
}

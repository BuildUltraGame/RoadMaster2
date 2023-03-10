// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RMBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API URMBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void ShowLogInBlueprint(FString logs);
};

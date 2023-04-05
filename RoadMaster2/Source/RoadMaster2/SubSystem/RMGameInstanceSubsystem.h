// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RMGameInstanceSubsystem.generated.h"

/**
 * Game实例SubSystem,持久化的内容在这里进行处理
 */
UCLASS()
class ROADMASTER2_API URMGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentInMapIndex;

	UPROPERTY(BlueprintReadWrite)
	TMap<int32,int32> NetIDToMapIndexTable;

	URMGameInstanceSubsystem();

	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Info.h"
#include "UnitInfoBase.generated.h"

class AMovableUnits;


USTRUCT()
struct FUnitDataStruct:public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Cost;
	UPROPERTY(EditAnywhere)
	float CoolDownSecond;
	UPROPERTY(EditAnywhere)
	int32 UnitAmount;
	UPROPERTY(EditAnywhere)
	float UnitInterval;	
}; 

/**
 * 存储基础的单位数据的数据类
 */
UCLASS(notplaceable, BlueprintType, Blueprintable)
class ROADMASTER2_API AUnitInfoBase : public AInfo
{
	GENERATED_BODY()
public:
	//单位消耗
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Cost;

	//CD
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CoolDownSecond;

	//单位数量
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 UnitAmount;

	//单位生成间隔
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float UnitInterval;

	//关联的Unit
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AMovableUnits> UnitClass;

	//关联的CardUI
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> CardIcon;
	
	AUnitInfoBase();

	UFUNCTION()
	void DoDataOverride();
	
protected:
	virtual void BeginPlay() override;
};

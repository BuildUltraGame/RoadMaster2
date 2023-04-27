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
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (Tooltip = "单位消耗"))
	int32 Cost;

	//CD
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (Tooltip = "单位冷却时间"))
	float CoolDownSecond;

	//单位数量
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (Tooltip = "一组该单位的数量"))
	int32 UnitAmount;

	//单位生成间隔
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (Tooltip = "单位组间间隔时间"))
	float UnitInterval;

	//是否是可拖拽单位
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (Tooltip = "单位是否可拖拽"))
	bool IsDragAble;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (Tooltip = "该单位是否一定要沿路行驶"))
	bool MustMoveOnRoad;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta = (Tooltip = "单位线速度"))
	int32 LinearSpeed;
	
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

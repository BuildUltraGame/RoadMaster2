// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "UnitLauncherComponent.generated.h"

class ALandFormPawn;
class AMovableUnits;
/**
 *  操作NavigationComponent,力的施与者
 */
UCLASS()
class ROADMASTER2_API UUnitLauncherComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChangeNavigator(AMovableUnits* Unit);

	UPROPERTY(BlueprintReadWrite)
	ALandFormPawn* LandFormOwner;

	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoadMaster2/LandForm/LandFormPawn.h"
#include "NavigationComponent.generated.h"

/**
 * 
 */
UCLASS()
class ROADMASTER2_API UNavigationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	ALandFormPawn* StartLand;

	UPROPERTY(BlueprintReadWrite)
	ALandFormPawn* EndLand;

	UPROPERTY()
	AMovableUnits* OwnerUnit;
	
	UFUNCTION(BlueprintCallable)
	void InitNavigator(AMovableUnits* Owner);

	UFUNCTION(BlueprintCallable)
	void Navigate(ALandFormPawn* Destination);
};

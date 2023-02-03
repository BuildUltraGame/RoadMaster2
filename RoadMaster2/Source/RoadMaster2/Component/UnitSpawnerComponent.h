// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UnitSpawnerComponent.generated.h"


class ALandFormPawn;
class AMovableUnits;
/**
 *  生成Unit的组件
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROADMASTER2_API UUnitSpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitSpawnerComponent();

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void SpawnUnit_Server();

	UFUNCTION(BlueprintCallable)
	void ForceRefreshSpawnerNavigator(AMovableUnits* NewUnit);
	
	UPROPERTY(BlueprintReadWrite)
	ALandFormPawn* LandFormOwner;

	//UFUNCTION(BlueprintCallable,NetMulticast,Reliable)
	//AMovableUnits* SpawnUnit_Multicast();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

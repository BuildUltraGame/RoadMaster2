// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSpawnerComponent.h"
#include "RoadMaster2/Units/MovableUnits.h"

// Sets default values for this component's properties
UUnitSpawnerComponent::UUnitSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnitSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUnitSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
// todo:增加单位信息对应配置
void UUnitSpawnerComponent::SpawnUnit_Server_Implementation()
{
	UWorld* World = GetWorld();
	//生成一个新单位
	AMovableUnits* NewUnit = World->SpawnActor<AMovableUnits>(GetComponentLocation(),GetComponentRotation());
	//初始化单位信息，包括其组件
	NewUnit->InitUnitByType(LandFormOwner);
	//首次生成，强制进行一次导航操作
	ForceRefreshSpawnerNavigator(NewUnit);
}


void UUnitSpawnerComponent::ForceRefreshSpawnerNavigator(AMovableUnits* NewUnit)
{
	if (NewUnit&&NewUnit->CanBeLaunched)
	{
		ALandFormPawn* NextLandForm = LandFormOwner->GetTargetPointByInput(NewUnit);
		NewUnit->Navigator->Navigate(LandFormOwner,NextLandForm);
	}
}


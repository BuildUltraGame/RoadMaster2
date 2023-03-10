// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableUnits.h"

// Sets default values
AMovableUnits::AMovableUnits()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovableUnits::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovableUnits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovableUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

ALandFormPawn* AMovableUnits::GetStartLand()
{
	if (Navigator)
	{
		return Navigator->StartLand;
	}
	return nullptr;
}

void AMovableUnits::InitUnitByType(ALandFormPawn* StartLand)
{
	Navigator = CreateDefaultSubobject<UNavigationComponent>(TEXT("Navigator"));
	Spawner = StartLand;
	Navigator->InitNavigator(this);
}

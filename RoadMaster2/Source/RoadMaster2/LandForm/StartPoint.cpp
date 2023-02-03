// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPoint.h"

#include "EnhancedInputComponent.h"
#include "RoadMaster2/Component/UnitSpawnerComponent.h"
#include "RoadMaster2/Units/MovableUnits.h"

void AStartPoint::BeginPlay()
{
	UnitSpawner = CreateDefaultSubobject<UUnitSpawnerComponent>(TEXT("UnitSpawner"));
	UnitSpawner->LandFormOwner = this;
}

void AStartPoint::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(TestSpawnAction, ETriggerEvent::Triggered, this, &AStartPoint::SpawnUnit);
	
	}

}

void AStartPoint::SpawnUnit(const FInputActionValue& Value)
{
	UnitSpawner->SpawnUnit_Server();
}



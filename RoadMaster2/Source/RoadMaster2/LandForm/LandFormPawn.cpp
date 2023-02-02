// Fill out your copyright notice in the Description page of Project Settings.


#include "LandFormPawn.h"

#include "ShaderPrintParameters.h"

// Sets default values
ALandFormPawn::ALandFormPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALandFormPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALandFormPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALandFormPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ALandFormPawn::GetWayPoint()
{
	if (IsValid(WayPoint))
	{
		return WayPoint->GetActorPositionForRenderer();
	}
	return FVector::Zero();
}



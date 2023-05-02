// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableUnits.h"

#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "RoadMaster2/Pawns/LandForm/LandFormPawn.h"

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
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("UnitLauncher"));
	Collider->SetupAttachment(RootComponent);
	Collider->OnComponentBeginOverlap.AddDynamic(this,&AMovableUnits::OnCollision);
}

// Called every frame
void AMovableUnits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovableUnits::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMovableUnits,MustMoveOnLine);
	DOREPLIFETIME(AMovableUnits,LinearSpeed);
	DOREPLIFETIME(AMovableUnits,Spawner);
	DOREPLIFETIME(AMovableUnits,ComingTrack);
	DOREPLIFETIME(AMovableUnits,CurrentTrack);
	DOREPLIFETIME(AMovableUnits,Destination);
	DOREPLIFETIME(AMovableUnits,PlayerIndex);
}

// Called to bind functionality to input
void AMovableUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMovableUnits::InitUnitByType(ALandFormPawn* StartLand, FVector InDestination)
{
	Spawner = StartLand;
	Destination = InDestination;
	PlayerIndex = StartLand->PlayerIndex;
}

void AMovableUnits::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

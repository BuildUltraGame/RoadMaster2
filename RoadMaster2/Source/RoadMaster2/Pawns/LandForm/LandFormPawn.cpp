// Fill out your copyright notice in the Description page of Project Settings.


#include "LandFormPawn.h"
#include "RoadMaster2/Pawns/Units/MovableUnits.h"
#include "ShaderPrintParameters.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ALandFormPawn::ALandFormPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("UnitLauncher"));
	Collider->SetupAttachment(RootComponent);
	Collider->OnComponentBeginOverlap.AddDynamic(this,&ALandFormPawn::OnCollision);
	PlayerIndex = -1;
	WorkAble = true;
}


void ALandFormPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALandFormPawn,Collider);
	DOREPLIFETIME(ALandFormPawn,ConnectedTrackList);
	DOREPLIFETIME(ALandFormPawn,PlayerIndex);
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

void ALandFormPawn::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ALandFormPawn::ExecUnitCollision(AMovableUnits* Unit)
{
	
	
}

bool ALandFormPawn::ExecLandformEffect(AMovableUnits* Unit)
{
	return false;
}

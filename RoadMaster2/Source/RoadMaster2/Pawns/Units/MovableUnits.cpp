// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableUnits.h"

#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "RoadMaster2/Pawns/LandForm/LandFormPawn.h"
#include "RoadMaster2/Pawns/Track/Track.h"

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
	DOREPLIFETIME(AMovableUnits,LinearSpeed);
	DOREPLIFETIME(AMovableUnits,CurrentTrack);
}

// Called to bind functionality to input
void AMovableUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMovableUnits::InitUnitByType_Implementation(ALandFormPawn* StartLand, FVector InDestination)
{
	Spawner = StartLand;
	Destination = InDestination;
	PlayerIndex = StartLand->PlayerIndex;
}

void AMovableUnits::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//服务器上结算碰撞
	if (GIsServer)
	{
		auto ComingActor = static_cast<ALandFormPawn*>(Other);
		if (IsValid(ComingActor))
		{
			ExecUnitCollision(ComingActor);
		}
	}	
}

void AMovableUnits::ExecUnitCollision(ALandFormPawn* LandForm)
{
	if (MustMoveOnLine)
	{
		FConnectedTrack* LeavingTrack = nullptr;
		if (LandForm->ConnectedTrackList.Num()>0)
		{
			for (auto ConnectedTrack : LandForm->ConnectedTrackList)
			{
				//不会被阻塞 todo 有点难以判断该情况
				if (!JamAble)
				{
					
				}
				//来路不通
				if (CurrentTrack == ConnectedTrack.Track && ConnectedTrack.IsJam)
				{
					LeavingTrack = &ConnectedTrack;
					break;
				}
				//去路不通
				if (ConnectedTrack.IsJam)
				{
					continue;
				}
				//去路可通，遍历至最后一个不做break
				if (ConnectedTrack.Track != CurrentTrack)
				{
					LeavingTrack = &ConnectedTrack;
				}
			}
		}
		//无路可走 返回
		if (LeavingTrack == nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("ExecUnitCollision No Place To Go!"));
			return;
		}
		//处理转线操作
		CurrentTrack = LeavingTrack->Track;
		CurrentTrack->AddUnitToTrack(this);
	}	
}

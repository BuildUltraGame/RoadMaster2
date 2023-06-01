// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableUnits.h"

#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "RoadMaster2/Pawns/LandForm/LandFormPawn.h"
#include "RoadMaster2/Pawns/Track/Track.h"
#include "RoadMaster2/Tools/RMBlueprintFunctionLibrary.h"

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
	DOREPLIFETIME(AMovableUnits,Spawner);
	DOREPLIFETIME(AMovableUnits,Destination);
	DOREPLIFETIME(AMovableUnits,PlayerIndex);
	DOREPLIFETIME(AMovableUnits,UnitID);
}

// Called to bind functionality to input
void AMovableUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMovableUnits::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//服务器上结算碰撞
	if (URMBlueprintFunctionLibrary::IsServer())
	{
		auto EnterLandForm = static_cast<ALandFormPawn*>(Other);
		if (IsValid(EnterLandForm))
		{
			ExecUnitCollision(EnterLandForm);
		}
	}	
}

void AMovableUnits::ExecUnitCollision(ALandFormPawn* LandForm)
{
	//首先尝试断开上一条track的链接
	if (IsValid(CurrentTrack))
	{
		CurrentTrack->RemoveUnitFromTrack(this);
	}
	//执行地形对单位的操作
	if (LandForm->ExecLandformEffect(this))
	{
		return;
	}
	//执行单位对地形的操作
	if (ExecUnitToLandformEffect(LandForm))
	{
		return;
	}
	//转线操作 优先级最低
	if (MustMoveOnLine)
	{
		FConnectedTrack* LeavingTrack = nullptr;
		if (LandForm->ConnectedTrackList.Num()>0)
		{
			for (auto &ConnectedTrack : LandForm->ConnectedTrackList)
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

bool AMovableUnits::ExecUnitToLandformEffect(ALandFormPawn* LandForm)
{
	return false;
}

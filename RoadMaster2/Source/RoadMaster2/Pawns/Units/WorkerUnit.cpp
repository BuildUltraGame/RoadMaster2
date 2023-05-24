// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerUnit.h"

#include "RoadMaster2/Pawns/LandForm/LandFormPawn.h"

AWorkerUnit::AWorkerUnit()
{
	MustMoveOnLine = true;
	IsStopAtDestination = true;
	JamAble = false;
}

void AWorkerUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);
}

bool AWorkerUnit::ExecUnitToLandformEffect(ALandFormPawn* LandForm)
{
	bool IsActiveOver = false;
	//扳动道闸
	if (LandForm->WorkAble)
	{
		int32 TrackCount = LandForm->ConnectedTrackList.Num();
		for (auto &Track : LandForm->ConnectedTrackList)
		{
			//两条连接道路，通与不通交换
			if (TrackCount == 2)
			{
				IsActiveOver = true;
				if (Track.IsJam == true)
				{
					Track.IsJam = false;
				}
				else
				{
					Track.IsJam = true;
				}
			}
			//三条连接道路，指定一条通行
			if (TrackCount == 3)
			{
				IsActiveOver = true;
				if (Track.IsJam == true)
				{
					Track.IsJam = false;
				}
				else
				{
					if (Track.Sign == TargetSign)
					{
						Track.IsJam = false;
					}
					else
					{
						Track.IsJam = true;
					}
				}				
			}
			//四条连接道路，通与不通交换
			if (TrackCount == 4)
			{
				IsActiveOver = true;
				if (Track.IsJam == true)
				{
					Track.IsJam = false;
				}
				else
				{
					Track.IsJam = true;
				}
			}
		}
		return IsActiveOver;
	}
	return Super::ExecUnitToLandformEffect(LandForm);
}

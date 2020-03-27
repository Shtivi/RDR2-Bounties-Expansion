#pragma once

enum BountyMissionStage
{
	MissionInitialization = -1,
	CollectPoster = 0,
	GoToArea = 1,
	LocateTarget = 2,
	CaptureTarget = 3,
	ArriveToPoliceStation = 4,
	HandOverTarget = 5,
	CollectReward = 6,
	Finished = 7
};

enum BountyMissionStatus {
	Unavailable = -1,
	Pending = 0,
	CollectedPoster = 1,
	InProgress = 2,
	Completed = 3,
	Failed = 4
};

enum TargetCondition
{
	Alive,
	DeadOrAlive
};

enum MapAreas
{
	Blackwater = 1,
	Rhodes,
	SaintDenis,
	Valentine,
	Strawberry,
	Annesburg
};

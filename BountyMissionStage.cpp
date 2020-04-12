#include "Main.h";

BountyMissionStage& operator++(BountyMissionStage& stage)
{
	switch (stage)
	{
		case BountyMissionStage::MissionInitialization:	return stage = BountyMissionStage::CollectPoster;
		case BountyMissionStage::CollectPoster:			return stage = BountyMissionStage::GoToArea;
		case BountyMissionStage::GoToArea:				return stage = BountyMissionStage::LocateTarget;
		case BountyMissionStage::LocateTarget:			return stage = BountyMissionStage::CaptureTarget;
		case BountyMissionStage::CaptureTarget:			return stage = BountyMissionStage::ArriveToPoliceStation;
		case BountyMissionStage::ArriveToPoliceStation:	return stage = BountyMissionStage::HandOverTarget;
		case BountyMissionStage::HandOverTarget:		return stage = BountyMissionStage::CollectReward;
		case BountyMissionStage::CollectReward:			return stage = BountyMissionStage::Finished;
	}
}
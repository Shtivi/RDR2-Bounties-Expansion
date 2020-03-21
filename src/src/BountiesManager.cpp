#include "Main.h";

//std::vector<BaseMissionExecutor*> missionExecutors;

BaseMissionExecutor* mission;

void initializeEliasTradition()
{
	BountyMissionData data;
	data.ordinal = 1;
	data.area = Blackwater;
	data.missionName = "Elias's tradition";
	data.crime = "Kidnapping";
	data.description = "Blah blah";
	data.requiredTargetCondition = DeadOrAlive;
	data.reward = 120;
	data.startPosition.x = -2032.61;
	data.startPosition.y = -1909.63;
	data.startPosition.z = 110.051;
	data.isTargetMale = true;
	data.targetName = "Elsie Green";

	//missionExecutors.push_back(new BaseMissionExecutor(data));
	mission = new EliasTraditionExecutor(data);
}

void initializeBounties()
{
	initializeEliasTradition();
}

void updateMissions()
{
	if (mission->getMissionStatus() < BountyMissionStatus::Completed)
	{
		mission->update();
	}
}
#include "Main.h";

//std::vector<BaseMissionExecutor*> missionExecutors;

BaseMissionExecutor* mission;

void initializeSkinnerBrothersKidnapping()
{
	BountyMissionData data;
	data.area = Blackwater;
	data.missionName = "Elias's tradition";
	data.crime = "Kidnapping";
	data.description = "Blah blah";
	data.requiredTargetCondition = Alive;
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
	initializeSkinnerBrothersKidnapping();
}

void updateMissions()
{
	if (mission->getMissionStatus() < BountyMissionStatus::Completed)
	{
		mission->update();
	}
}
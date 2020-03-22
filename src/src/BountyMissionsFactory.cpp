#include "Main.h";

BountyMissionsFactory::BountyMissionsFactory(MapAreasManager* areasMgr)
{
	this->areasMgr = areasMgr;
	initializeCache();
}

bool BountyMissionsFactory::doesMissionExist(int missionId)
{
	return (cache.find(missionId) != cache.end());
}

BaseMissionExecutor* BountyMissionsFactory::fromMissionId(int missionId)
{
	if (cache.find(missionId) != cache.end())
	{
		return cache.find(missionId)->second;
	}

	return NULL;
}

void BountyMissionsFactory::initializeCache()
{
	cache[1] = eliasTraditionExecutor();
}

EliasTraditionExecutor* BountyMissionsFactory::eliasTraditionExecutor()
{
	BountyMissionData data;
	data.id = 1;
	data.area = Blackwater;
	data.missionName = "Elias's Tradition";
	data.crime = "Murder";
	data.description = "He is the brother of Elias Green,\nboth are members of the infamous Skinner Brothers.\nWanted for murdering a nearby farmers.";
	data.requiredTargetCondition = DeadOrAlive;
	data.reward = 120;
	data.rewardStr = "120$";
	data.startPosition.x = -2032.61;
	data.startPosition.y = -1909.63;
	data.startPosition.z = 110.051;
	data.isTargetMale = true;
	data.targetName = "Elsie Green";

	return new EliasTraditionExecutor(data, areasMgr);

}
#include "Main.h";

BountyMissionsFactory::BountyMissionsFactory(MapAreasManager* areasMgr)
{
	this->areasMgr = areasMgr;
	initializeCache();
}

bool BountyMissionsFactory::doesMissionExist(int missionId)
{
	return (executorsCache.find(missionId) != executorsCache.end());
}

BaseMissionExecutor* BountyMissionsFactory::fromMissionId(int missionId)
{
	if (executorsCache.find(missionId) != executorsCache.end())
	{
		return executorsCache.find(missionId)->second;
	}

	return NULL;
}

std::vector<int> BountyMissionsFactory::getAllMissionIds()
{
	std::vector<int> missionsData;
	std::map<int, BaseMissionExecutor*>::iterator it = executorsCache.begin();

	while(it != executorsCache.end())
	{
		missionsData.push_back((*it).second->getMissionData()->id);
		++it;
	}

	std::sort(missionsData.begin(), missionsData.end());
	return missionsData;
}

void BountyMissionsFactory::initializeCache()
{
	executorsCache[1] = eliasTraditionExecutor();
	executorsCache[2] = turkishRunnerExecutor();
	executorsCache[3] = jacobSeedExecutor();
	executorsCache[4] = andrewClarkExecutor();

	map<int, BaseMissionExecutor*>::iterator it = executorsCache.begin();
	BaseMissionExecutor* curr;
	while (it != executorsCache.end())
	{
		curr = (*it).second;
		areasMgr->getMapArea(curr->getMissionData()->area)->linkMission(curr->getMissionData()->id);
		++it;
	}
}

EliasTraditionExecutor* BountyMissionsFactory::eliasTraditionExecutor()
{
	BountyMissionData data;
	data.id = 1;
	data.area = MapAreas::Blackwater;
	data.missionName = "Elias's Tradition";
	data.crime = "Murder";
	data.description = "He is the brother of Elias Green,\nboth are members of the infamous Skinner Brothers.\nWanted for murdering a nearby farmers.\nHe is extremely aggresive and dangerous.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 150;
	data.rewardStr = "$150";
	data.startPosition.x = -2032.61;
	data.startPosition.y = -1909.63;
	data.startPosition.z = 110.051;
	data.isTargetMale = true;
	data.targetName = "Elsie Green";

	return new EliasTraditionExecutor(data, areasMgr);
}

TurkishRunnerExecutor* BountyMissionsFactory::turkishRunnerExecutor()
{
	BountyMissionData data;
	data.id = 2;
	data.area = MapAreas::Blackwater;
	data.missionName = "The Turkish Runner";
	data.crime = "Horse theft";
	data.description = "He wanted for stealing a rare horse\nfrom the stables in Blackwater.\nThe suspect is a mexican, middle aged male.\nLast seen near Macfarlande's ranch.\nBe aware, he could be armed.";
	data.requiredTargetCondition = TargetCondition::Alive;
	data.reward = 180;
	data.rewardStr = "$180";
	data.startPosition = toVector3(-2758.81, -2690.14, 87.4308);
	data.isTargetMale = true;
	data.targetName = "Alejandro Hernandez";

	return new TurkishRunnerExecutor(data, areasMgr);
}

JacobSeedExecutor* BountyMissionsFactory::jacobSeedExecutor()
{
	BountyMissionData data;
	data.id = 3;
	data.area = MapAreas::Rhodes;
	data.missionName = "Jacob Seed";
	data.crime = "Fire Arms Theft";
	data.description = "Jacob Seed is the leader of a local\nLemoyne Raiders group.\nHe is wanted for robbing a firearms delivery\non its way to Fort Wallace.\nHe and his gang are extremely dangerous.";
	data.requiredTargetCondition = TargetCondition::Alive;
	data.reward = 220;
	data.rewardStr = "$220";
	data.startPosition = toVector3(1570.67, -439.573, 65.966);
	data.isTargetMale = true;
	data.targetName = "Jacob Seed";

	return new JacobSeedExecutor(data, areasMgr);
}

AndrewClarkExecutor* BountyMissionsFactory::andrewClarkExecutor()
{
	BountyMissionData data;
	data.id = 4;
	data.area = MapAreas::Valentine;
	data.missionName = "Andrew Clark";
	data.crime = "Fraud and Theft";
	data.description = "He had been working for the bank of Valentine\nfor years and was found guilty of\nstealing the bank's money.\nLast known whereabouts was north of Valentine.";
	data.requiredTargetCondition = TargetCondition::Alive;
	data.reward = 120;
	data.rewardStr = "$120";
	data.startPosition = toVector3(-364.596, 1263.53, 141.176);
	data.isTargetMale = true;
	data.targetName = "Andrew Clark";

	return new AndrewClarkExecutor(data, areasMgr);
}

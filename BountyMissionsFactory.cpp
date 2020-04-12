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
	executorsCache[5] = jesseHillExecutor();
	executorsCache[6] = quentinChigurhExecutor();
	executorsCache[7] = tucoVillaExecutor();

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

JesseHillExecutor* BountyMissionsFactory::jesseHillExecutor()
{
	BountyMissionData data;
	data.id = 5;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "Jesse Hill";
	data.crime = "Murder";
	data.description = "Jesse Hill, wanted for murder.\nKiller of husband and wife in cold blood.\nHe's known to be hiding in the hills of New Austin, armed and dangerous.\n";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 95;
	data.rewardStr = "$95";
	data.startPosition = toVector3(-5710.177, -2386.995, 6.257581);
	data.isTargetMale = true;
	data.targetName = "Jesse Hill";

	return new JesseHillExecutor(data, areasMgr);
}

QuentinChigurhExecutor* BountyMissionsFactory::quentinChigurhExecutor()
{
	BountyMissionData data;
	data.id = 6;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "Quentin Chigurh";
	data.crime = "Train Robbery";
	data.description = "Quentin Chigurh, wanted for the stolen goods and\n several casualties aboard the New Austin Express.\nIt's rumored he's headed for mexico and \nwaiting for a boat along the river.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 150;
	data.rewardStr = "$150";
	data.startPosition = toVector3(-6451.273, -3538.335, -25.54377);
	data.isTargetMale = true;
	data.targetName = "Quentin Chigurh";

	return new QuentinChigurhExecutor(data, areasMgr);
}

TucoVillaExecutor* BountyMissionsFactory::tucoVillaExecutor()
{
	BountyMissionData data;
	data.id = 7;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "Tuco Villa";
	data.crime = "Double Murder";
	data.description = "Tuco Villa, known as Tuco del Diablo.\n This mexican bandito has been found guilty of double homicide\n of a local farmer and his son. Due to his\n connections with the del Lobo gang he's managed to\n escape his captivity and is believed to be hiding\n in the hills of New Austin.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 100;
	data.rewardStr = "$100";
	data.startPosition = toVector3(-5053.802, -3629.418, -4.846035);
	data.isTargetMale = true;
	data.targetName = "Tuco Villa";

	return new TucoVillaExecutor(data, areasMgr);
}
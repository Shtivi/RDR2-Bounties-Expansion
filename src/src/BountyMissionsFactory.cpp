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
	executorsCache[3] = gushkalaInataExecutor();
	executorsCache[4] = jacobSeedExecutor();
	executorsCache[5] = andrewClarkExecutor();
	executorsCache[6] = chesterBurnettExecutor();
	executorsCache[7] = jesseHillExecutor();
	executorsCache[8] = quentinChigurhExecutor();
	executorsCache[9] = tucoVillaExecutor();
	executorsCache[10] = archStantonExecutor();
	executorsCache[11] = richardMooreExecutor();
	executorsCache[12] = juanCortezExecutor();
	executorsCache[13] = clintonvonHagenExecutor();
	executorsCache[14] = treasuryPeteExecutor();
	executorsCache[15] = robertCorbucciExecutor();
	executorsCache[16] = janeBullionExecutor();

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

GushkalaInataExecutor* BountyMissionsFactory::gushkalaInataExecutor()
{
	BountyMissionData data;
	data.id = 3;
	data.area = MapAreas::Blackwater;
	data.missionName = "GushkalaInata";
	data.crime = "Robbing";
	data.description = "Gushkala Inata known as Hidden Snake\npractices a particular skill when it comes to crime.\nHe is known to rob and kill people who cross his\npath and then hides the forest of Tall of Trees.\nSo far not a single lawman has been able\nto find him, hence a bounty has been\nput on his head for capture.";
	data.requiredTargetCondition = TargetCondition::Alive;
	data.reward = 165;
	data.rewardStr = "$165";
	data.startPosition = toVector3(-2324.694, -1440.603, 151.5746);
	data.isTargetMale = true;
	data.targetName = "Gushkala Inata";

	return new GushkalaInataExecutor(data, areasMgr);
}

JacobSeedExecutor* BountyMissionsFactory::jacobSeedExecutor()
{
	BountyMissionData data;
	data.id = 4;
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
	data.id = 5;
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

ChesterBurnettExecutor* BountyMissionsFactory::chesterBurnettExecutor()
{
	BountyMissionData data;
	data.id = 6;
	data.area = MapAreas::Valentine;
	data.missionName = "ChesterBurnett";
	data.crime = "Murder";
	data.description = "Chester Burnett is a murdering crook on the run\nfrom the law. One of four passengers last seen\nleaving Strawberry. It is thought due to\na blizzard they have been keeping shelter in colter.\nOne of these passengers is Burnett. Be careful \nhowever, we do not want any innocent bloodshed,\nso if you kill or capture the wrong man by\n accident you will not be paid.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 130;
	data.rewardStr = "$130";
	data.startPosition = toVector3(-1353.869, 2440.07, 308.4282);
	data.isTargetMale = true;
	data.targetName = "Chester Burnett";

	return new ChesterBurnettExecutor(data, areasMgr);
}

JesseHillExecutor* BountyMissionsFactory::jesseHillExecutor()
{
	BountyMissionData data;
	data.id = 7;
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
	data.id = 8;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "Quentin Chigurh";
	data.crime = "Train Robbery";
	data.description = "Quentin Chigurh, wanted for the stolen goods and\n several casualties aboard the New Austin Express.\nIt's rumored he's headed for mexico and \nwaiting for a boat along the river.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 120;
	data.rewardStr = "$120";
	data.startPosition = toVector3(-6451.273, -3538.335, -25.54377);
	data.isTargetMale = true;
	data.targetName = "Quentin Chigurh";

	return new QuentinChigurhExecutor(data, areasMgr);
}

TucoVillaExecutor* BountyMissionsFactory::tucoVillaExecutor()
{
	BountyMissionData data;
	data.id = 9;
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

ArchStantonExecutor* BountyMissionsFactory::archStantonExecutor()
{
	BountyMissionData data;
	data.id = 10;
	data.area = MapAreas::Armadillo;
	data.missionName = "Arch Stanton";
	data.crime = "Stagecoach robbery";
	data.description = "Arch Stanton, a bandit guilty of robbing multiple stagecoaches.\nHe is not one to leave witnesses to his crimes which earned him a dead or alive bounty.\nDue to the cholera outbreak prices have been cut, we know this isn't the way it's supposed to work\n so if not for the money then for your fellow american.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 40;
	data.rewardStr = "$40";
	data.startPosition = toVector3(-3508.315, -1967.514, 4.799573);
	data.isTargetMale = true;
	data.targetName = "Arch Stanton";

	return new ArchStantonExecutor(data, areasMgr);
}

RichardMooreExecutor* BountyMissionsFactory::richardMooreExecutor()
{
	BountyMissionData data;
	data.id = 11;
	data.area = MapAreas::Armadillo;
	data.missionName = "Richard Moore";
	data.crime = "Murder and Robbery";
	data.description = "After 3 years of his failed attempt to rob the \nArmadillo bank the bandit known as Richard the Renegade\n has shown his face once again in New\n Austin rumored to be hiding in caves within\n the hills with a few of his robbery members left";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 45;
	data.rewardStr = "$45";
	data.startPosition = toVector3(-4388.753, -2161.34, 49.57555);
	data.isTargetMale = true;
	data.targetName = "Richard Moore";

	return new RichardMooreExecutor(data, areasMgr);
}

JuanCortezExecutor* BountyMissionsFactory::juanCortezExecutor()
{
	BountyMissionData data;
	data.id = 12;
	data.area = MapAreas::Armadillo;
	data.missionName = "Juan Cortez";
	data.crime = "Murder";
	data.description = "Bandito from mexico, guilty for the murder of a woman.\nWanted dead or alive, he has since then joined \nup with the del lobo gang. Blieved to \nbe help up in one of their cottages.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 35;
	data.rewardStr = "$35";
	data.startPosition = toVector3(-3484.982, -3468.916, 0.1763178);
	data.isTargetMale = true;
	data.targetName = "Juan Cortez";

	return new JuanCortezExecutor(data, areasMgr);
}

ClintonvonHagenExecutor* BountyMissionsFactory::clintonvonHagenExecutor()
{
	BountyMissionData data;
	data.id = 13;
	data.area = MapAreas::SaintDenis;
	data.missionName = "Clinton von Hagen";
	data.crime = "Murder";
	data.description = "Clinton von Hagen has been found guilty for the Murder or \nMyrtle Stevenson, head of local women suffrage\nmovement, this impotant murderer thought to enhance\nhis political views by feeding her to the lemoyne\naligators. Got himself a death warrent instead.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 150;
	data.rewardStr = "$150";
	data.startPosition = toVector3(1874.233, -540.7623, 44.48211);
	data.isTargetMale = true;
	data.targetName = "Clinton von Hagen";

	return new ClintonvonHagenExecutor(data, areasMgr);
}

TreasuryPeteExecutor* BountyMissionsFactory::treasuryPeteExecutor()
{
	BountyMissionData data;
	data.id = 14;
	data.area = MapAreas::SaintDenis;
	data.missionName = "TreasuryPete";
	data.crime = "Bank Robbery";
	data.description = "Peter Broadwell, was a money laundering crook who\nthought after his sherade was uncovered he could\nmake a final bout by robbing the Saint Denis bank.\nNo money was lost however, several lives were.\nSources claim he waiting for a boat to take him to his\nrefuge with his fellow robbers.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 150;
	data.rewardStr = "$150";
	data.startPosition = toVector3(2884.414, -244.7007, 41.77635);
	data.isTargetMale = true;
	data.targetName = "Treasury Pete";

	return new TreasuryPeteExecutor(data, areasMgr);
}

RobertCorbucciExecutor* BountyMissionsFactory::robertCorbucciExecutor()
{
	BountyMissionData data;
	data.id = 15;
	data.area = MapAreas::SaintDenis;
	data.missionName = "RobertCorbucci";
	data.crime = "Murder";
	data.description = "Robert Corbucci is a former associate of Guido Martelli.\nWord on the street is things didn't quite workout between\nhim and the new management. To prevent further street\njustice, the state of Lemoyne has put a bounty\non his head to bring him in dead or alive.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 160;
	data.rewardStr = "$160";
	data.startPosition = toVector3(1261.292, -419.4841, 95.66013);
	data.isTargetMale = true;
	data.targetName = "Robert Corbucci";

	return new RobertCorbucciExecutor(data, areasMgr);
}

JaneBullionExecutor* BountyMissionsFactory::janeBullionExecutor()
{
	BountyMissionData data;
	data.id = 16;
	data.area = MapAreas::SaintDenis;
	data.missionName = "JaneBullion";
	data.crime = "Multiple counts of theft";
	data.description = "Jane Bullion has been charged with multiple counts\nof theft throughout Saint Denis, earning her the name Runaway Jane.\nDue to her violentless way of crime she is wanted alive.\nKeep your eyes sharp however, for her name is not\njust given out of pity. She has been recognized to be near\nrhodes after her bounty was set up";
	data.requiredTargetCondition = TargetCondition::Alive;
	data.reward = 65;
	data.rewardStr = "$65";
	data.startPosition = toVector3(1452.836, -1580.975, 72.01614);
	data.isTargetMale = false;
	data.targetName = "Jane Bullion";

	return new JaneBullionExecutor(data, areasMgr);
}

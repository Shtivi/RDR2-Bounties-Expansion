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
	executorsCache[4] = hankEnepayExecutor();
	executorsCache[5] = nateNashobaExecutor();
	executorsCache[6] = charlesMoonExecutor();
	executorsCache[7] = jacobSeedExecutor();
	executorsCache[8] = janeBullionExecutor();
	executorsCache[9] = bufordDukeExecutor();
	executorsCache[10] = harperConnorExecutor();
	executorsCache[11] = wallaceKnoxExecutor();
	executorsCache[12] = emmettDavisExecutor();
	executorsCache[13] = andrewClarkExecutor();
	executorsCache[14] = chesterBurnettExecutor();
	executorsCache[15] = cullenBakerExecutor();
	executorsCache[16] = johnBullExecutor();
	executorsCache[17] = marquisRussellExecutor();
	executorsCache[18] = peteEatonExecutor();
	executorsCache[19] = jesseHillExecutor();
	executorsCache[20] = quentinChigurhExecutor();
	executorsCache[21] = tucoVillaExecutor();
	executorsCache[22] = billyWilsonExecutor();
	executorsCache[23] = joseChavezExecutor();
	executorsCache[24] = panchoDanielExecutor();
	executorsCache[25] = archStantonExecutor();
	executorsCache[26] = richardMooreExecutor();
	executorsCache[27] = juanCortezExecutor();
	executorsCache[28] = clintonvonHagenExecutor();
	executorsCache[29] = carlMartinExecutor();
	executorsCache[30] = treasuryPeteExecutor();
	executorsCache[31] = robertCorbucciExecutor();
	executorsCache[32] = mikeSandersExecutor();
	executorsCache[33] = chrisJaniceExecutor();
	executorsCache[34] = justusBarnesExecutor();
	executorsCache[35] = williamRogersExecutor();
	executorsCache[36] = bobLaneExecutor();
	executorsCache[37] = georgeCoenExecutor();
	executorsCache[38] = buckHicoxExecutor();
	executorsCache[39] = johnEastwoodExecutor();

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
	data.reward = 75;
	data.rewardStr = "$75";
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
	data.reward = 50;
	data.rewardStr = "$50";
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
	data.reward = 80;
	data.rewardStr = "$80";
	data.startPosition = toVector3(-2324.694, -1440.603, 151.5746);
	data.isTargetMale = true;
	data.targetName = "Gushkala Inata";

	return new GushkalaInataExecutor(data, areasMgr);
}

HankEnepayExecutor* BountyMissionsFactory::hankEnepayExecutor()
{
	BountyMissionData data;
	data.id = 4;
	data.area = MapAreas::Blackwater;
	data.missionName = "HankEnepay";
	data.crime = "Murder and Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 90;
	data.rewardStr = "$90";
	data.startPosition = toVector3(-2357.136, -948.3532, 165.9597);
	data.isTargetMale = true;
	data.targetName = "Hank Enepay";

	return new HankEnepayExecutor(data, areasMgr);
}

NateNashobaExecutor* BountyMissionsFactory::nateNashobaExecutor()
{
	BountyMissionData data;
	data.id = 5;
	data.area = MapAreas::Blackwater;
	data.missionName = "NateNashoba";
	data.crime = "Murder and Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 75;
	data.rewardStr = "$75";
	data.startPosition = toVector3(-2575.68, -1371.892, 148.1127);
	data.isTargetMale = true;
	data.targetName = "Nate Nashoba";

	return new NateNashobaExecutor(data, areasMgr);
}

CharlesMoonExecutor* BountyMissionsFactory::charlesMoonExecutor()
{
	BountyMissionData data;
	data.id = 6;
	data.area = MapAreas::Blackwater;
	data.missionName = "CharlesMoon";
	data.crime = "Murder and Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 80;
	data.rewardStr = "$80";
	data.startPosition = toVector3(-1957.099, -2712.923, 67.1411);
	data.isTargetMale = true;
	data.targetName = "Charles Moon";

	return new CharlesMoonExecutor(data, areasMgr);
}

JacobSeedExecutor* BountyMissionsFactory::jacobSeedExecutor()
{
	BountyMissionData data;
	data.id = 7;
	data.area = MapAreas::Rhodes;
	data.missionName = "Jacob Seed";
	data.crime = "Fire Arms Theft";
	data.description = "Jacob Seed is the leader of a local\nLemoyne Raiders group.\nHe is wanted for robbing a firearms delivery\non its way to Fort Wallace.\nHe and his gang are extremely dangerous.";
	data.requiredTargetCondition = TargetCondition::Alive;
	data.reward = 60;
	data.rewardStr = "$60";
	data.startPosition = toVector3(1570.67, -439.573, 65.966);
	data.isTargetMale = true;
	data.targetName = "Jacob Seed";

	return new JacobSeedExecutor(data, areasMgr);
}

JaneBullionExecutor* BountyMissionsFactory::janeBullionExecutor()
{
	BountyMissionData data;
	data.id = 8;
	data.area = MapAreas::Rhodes;
	data.missionName = "JaneBullion";
	data.crime = "Multiple counts of theft";
	data.description = "Jane Bullion has been charged with multiple counts\nof theft throughout Saint Denis, earning her the name Runaway Jane.\nDue to her violentless way of crime she is wanted alive.\nKeep your eyes sharp however, for her name is not\njust given out of pity. She has been recognized to be near\nrhodes after her bounty was set up";
	data.requiredTargetCondition = TargetCondition::Alive;
	data.reward = 30;
	data.rewardStr = "$30";
	data.startPosition = toVector3(2114.806, -1277.321, 41.13449);
	data.isTargetMale = false;
	data.targetName = "Jane Bullion";

	return new JaneBullionExecutor(data, areasMgr);
}

BufordDukeExecutor* BountyMissionsFactory::bufordDukeExecutor()
{
	BountyMissionData data;
	data.id = 9;
	data.area = MapAreas::Rhodes;
	data.missionName = "BufordDuke";
	data.crime = "Fire Arms Theft";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 55;
	data.rewardStr = "$55";
	data.startPosition = toVector3(1585.817, -1851.348, 51.3534);
	data.isTargetMale = true;
	data.targetName = "Buford Duke";

	return new BufordDukeExecutor(data, areasMgr);
}

HarperConnorExecutor* BountyMissionsFactory::harperConnorExecutor()
{
	BountyMissionData data;
	data.id = 10;
	data.area = MapAreas::Rhodes;
	data.missionName = "HarperConnor";
	data.crime = "Fire Arms Theft";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 65;
	data.rewardStr = "$65";
	data.startPosition = toVector3(768.0861, -852.4528, 54.38295);
	data.isTargetMale = true;
	data.targetName = "Harper Connor";

	return new HarperConnorExecutor(data, areasMgr);
}

WallaceKnoxExecutor* BountyMissionsFactory::wallaceKnoxExecutor()
{
	BountyMissionData data;
	data.id = 11;
	data.area = MapAreas::Rhodes;
	data.missionName = "WallaceKnox";
	data.crime = "Fire Arms Theft";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 70;
	data.rewardStr = "$70";
	data.startPosition = toVector3(1382.377, -2081.04, 50.99044);
	data.isTargetMale = true;
	data.targetName = "Wallace Knox";

	return new WallaceKnoxExecutor(data, areasMgr);
}

EmmettDavisExecutor* BountyMissionsFactory::emmettDavisExecutor()
{
	BountyMissionData data;
	data.id = 12;
	data.area = MapAreas::Rhodes;
	data.missionName = "EmmettDavis";
	data.crime = "Fire Arms Theft";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 55;
	data.rewardStr = "$55";
	data.startPosition = toVector3(718.9932, -464.4996, 78.51635);
	data.isTargetMale = true;
	data.targetName = "Emmett Davis";

	return new EmmettDavisExecutor(data, areasMgr);
}

AndrewClarkExecutor* BountyMissionsFactory::andrewClarkExecutor()
{
	BountyMissionData data;
	data.id = 13;
	data.area = MapAreas::Valentine;
	data.missionName = "Andrew Clark";
	data.crime = "Fraud and Theft";
	data.description = "He had been working for the bank of Valentine\nfor years and was found guilty of\nstealing the bank's money.\nLast known whereabouts was north of Valentine.";
	data.requiredTargetCondition = TargetCondition::Alive;
	data.reward = 40;
	data.rewardStr = "$40";
	data.startPosition = toVector3(-364.596, 1263.53, 141.176);
	data.isTargetMale = true;
	data.targetName = "Andrew Clark";

	return new AndrewClarkExecutor(data, areasMgr);
}

ChesterBurnettExecutor* BountyMissionsFactory::chesterBurnettExecutor()
{
	BountyMissionData data;
	data.id = 14;
	data.area = MapAreas::Valentine;
	data.missionName = "ChesterBurnett";
	data.crime = "Murder";
	data.description = "Chester Burnett is a murdering crook on the run\nfrom the law. One of four passengers last seen\nleaving Strawberry. It is thought due to\na blizzard they have been keeping shelter in colter.\nOne of these passengers is Burnett. Be careful \nhowever, we do not want any innocent bloodshed,\nso if you kill or capture the wrong man by\n accident you will not be paid.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 65;
	data.rewardStr = "$65";
	data.startPosition = toVector3(-1353.869, 2440.07, 308.4282);
	data.isTargetMale = true;
	data.targetName = "Chester Burnett";

	return new ChesterBurnettExecutor(data, areasMgr);
}

CullenBakerExecutor* BountyMissionsFactory::cullenBakerExecutor()
{
	BountyMissionData data;
	data.id = 15;
	data.area = MapAreas::Valentine;
	data.missionName = "CullenBaker";
	data.crime = "Train Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 70;
	data.rewardStr = "$70";
	data.startPosition = toVector3(378.7642, -10.15373, 107.0928);
	data.isTargetMale = true;
	data.targetName = "Cullen Baker";

	return new CullenBakerExecutor(data, areasMgr);
}

JohnBullExecutor* BountyMissionsFactory::johnBullExecutor()
{
	BountyMissionData data;
	data.id = 16;
	data.area = MapAreas::Valentine;
	data.missionName = "JohnBull";
	data.crime = "Train Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 70;
	data.rewardStr = "$70";
	data.startPosition = toVector3(1256.149, 1161.379, 149.3029);
	data.isTargetMale = true;
	data.targetName = "John Bull";

	return new JohnBullExecutor(data, areasMgr);
}

MarquisRussellExecutor* BountyMissionsFactory::marquisRussellExecutor()
{
	BountyMissionData data;
	data.id = 17;
	data.area = MapAreas::Valentine;
	data.missionName = "MarquisRussell";
	data.crime = "Train Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 75;
	data.rewardStr = "$75";
	data.startPosition = toVector3(-1963.104, 2158.636, 326.5899);
	data.isTargetMale = true;
	data.targetName = "Marquis Russell";

	return new MarquisRussellExecutor(data, areasMgr);
}

PeteEatonExecutor* BountyMissionsFactory::peteEatonExecutor()
{
	BountyMissionData data;
	data.id = 18;
	data.area = MapAreas::Valentine;
	data.missionName = "PeteEaton";
	data.crime = "Train Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 65;
	data.rewardStr = "$65";
	data.startPosition = toVector3(1079.162, 115.801, 93.26965);
	data.isTargetMale = true;
	data.targetName = "Pete Eaton";

	return new PeteEatonExecutor(data, areasMgr);
}

JesseHillExecutor* BountyMissionsFactory::jesseHillExecutor()
{
	BountyMissionData data;
	data.id = 19;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "JesseHill";
	data.crime = "Murder";
	data.description = "Jesse Hill, wanted for murder.\nKiller of husband and wife in cold blood.\nHe's known to be hiding in the hills of New Austin, armed and dangerous.\n";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 60;
	data.rewardStr = "$60";
	data.startPosition = toVector3(-5660.05, -2396.66, -3.67743);
	data.isTargetMale = true;
	data.targetName = "Jesse Hill";

	return new JesseHillExecutor(data, areasMgr);
}

QuentinChigurhExecutor* BountyMissionsFactory::quentinChigurhExecutor()
{
	BountyMissionData data;
	data.id = 20;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "QuentinChigurh";
	data.crime = "Train Robbery";
	data.description = "Quentin Chigurh, wanted for the stolen goods and\n several casualties aboard the New Austin Express.\nIt's rumored he's headed for mexico and \nwaiting for a boat along the river.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 60;
	data.rewardStr = "$60";
	data.startPosition = toVector3(-6451.273, -3538.335, -25.54377);
	data.isTargetMale = true;
	data.targetName = "Quentin Chigurh";

	return new QuentinChigurhExecutor(data, areasMgr);
}

TucoVillaExecutor* BountyMissionsFactory::tucoVillaExecutor()
{
	BountyMissionData data;
	data.id = 21;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "TucoVilla";
	data.crime = "Double Murder";
	data.description = "Tuco Villa, known as Tuco del Diablo.\n This mexican bandito has been found guilty of double homicide\n of a local farmer and his son. Due to his\n connections with the del Lobo gang he's managed to\n escape his captivity and is believed to be hiding\n in the hills of New Austin.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 65;
	data.rewardStr = "$65";
	data.startPosition = toVector3(-5053.802, -3629.418, -4.846035);
	data.isTargetMale = true;
	data.targetName = "Tuco Villa";

	return new TucoVillaExecutor(data, areasMgr);
}

BillyWilsonExecutor* BountyMissionsFactory::billyWilsonExecutor()
{
	BountyMissionData data;
	data.id = 22;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "BillyWilson";
	data.crime = "Train Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 65;
	data.rewardStr = "$65";
	data.startPosition = toVector3(-4458.25, -3654.89, 57.7783);
	data.isTargetMale = true;
	data.targetName = "Billy Wilson";

	return new BillyWilsonExecutor(data, areasMgr);
}

JoseChavezExecutor* BountyMissionsFactory::joseChavezExecutor()
{
	BountyMissionData data;
	data.id = 23;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "JoseChavez";
	data.crime = "Train Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 55;
	data.rewardStr = "$55";
	data.startPosition = toVector3(-4484.039, -2865.338, -12.28567);
	data.isTargetMale = true;
	data.targetName = "Jose Chavez";

	return new JoseChavezExecutor(data, areasMgr);
}

PanchoDanielExecutor* BountyMissionsFactory::panchoDanielExecutor()
{
	BountyMissionData data;
	data.id = 24;
	data.area = MapAreas::Tumbleweed;
	data.missionName = "PanchoDaniel";
	data.crime = "Train Robbery";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 60;
	data.rewardStr = "$60";
	data.startPosition = toVector3(-3836.463, -3014.846, -8.249296);
	data.isTargetMale = true;
	data.targetName = "Pancho Daniel";

	return new PanchoDanielExecutor(data, areasMgr);
}

ArchStantonExecutor* BountyMissionsFactory::archStantonExecutor()
{
	BountyMissionData data;
	data.id = 25;
	data.area = MapAreas::Armadillo;
	data.missionName = "ArchStanton";
	data.crime = "Stagecoach robbery";
	data.description = "Arch Stanton, a bandit guilty of robbing multiple stagecoaches.\nHe is not one to leave witnesses to his crimes which earned him a dead or alive bounty.\nDue to the cholera outbreak prices have been cut, we know this isn't the way it's supposed to work\n so if not for the money then for your fellow american.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 30;
	data.rewardStr = "$30";
	data.startPosition = toVector3(-3508.315, -1967.514, 4.799573);
	data.isTargetMale = true;
	data.targetName = "Arch Stanton";

	return new ArchStantonExecutor(data, areasMgr);
}

RichardMooreExecutor* BountyMissionsFactory::richardMooreExecutor()
{
	BountyMissionData data;
	data.id = 26;
	data.area = MapAreas::Armadillo;
	data.missionName = "RichardMoore";
	data.crime = "Murder and Robbery";
	data.description = "After 3 years of his failed attempt to rob the \nArmadillo bank the bandit known as Richard the Renegade\n has shown his face once again in New\n Austin rumored to be hiding in caves within\n the hills with a few of his robbery members left";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 35;
	data.rewardStr = "$35";
	data.startPosition = toVector3(-4388.753, -2161.34, 49.57555);
	data.isTargetMale = true;
	data.targetName = "Richard Moore";

	return new RichardMooreExecutor(data, areasMgr);
}

JuanCortezExecutor* BountyMissionsFactory::juanCortezExecutor()
{
	BountyMissionData data;
	data.id = 27;
	data.area = MapAreas::Armadillo;
	data.missionName = "JuanCortez";
	data.crime = "Murder";
	data.description = "Bandito from mexico, guilty for the murder of a woman.\nWanted dead or alive, he has since then joined \nup with the del lobo gang. Believed to \nbe help up in one of their cottages.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 25;
	data.rewardStr = "$25";
	data.startPosition = toVector3(-3484.982, -3468.916, 0.1763178);
	data.isTargetMale = true;
	data.targetName = "Juan Cortez";

	return new JuanCortezExecutor(data, areasMgr);
}

ClintonvonHagenExecutor* BountyMissionsFactory::clintonvonHagenExecutor()
{
	BountyMissionData data;
	data.id = 28;
	data.area = MapAreas::SaintDenis;
	data.missionName = "ClintonvonHagen";
	data.crime = "Murder";
	data.description = "Clinton von Hagen has been found guilty for the Murder or \nMyrtle Stevenson, head of local women suffrage\nmovement, this impotant murderer thought to enhance\nhis political views by feeding her to the lemoyne\naligators. Got himself a death warrent instead.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 105;
	data.rewardStr = "$105";
	data.startPosition = toVector3(1874.233, -540.7623, 44.48211);
	data.isTargetMale = true;
	data.targetName = "Clinton von Hagen";

	return new ClintonvonHagenExecutor(data, areasMgr);
}

CarlMartinExecutor* BountyMissionsFactory::carlMartinExecutor()
{
	BountyMissionData data;
	data.id = 29;
	data.area = MapAreas::SaintDenis;
	data.missionName = "CarlMartin";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 100;
	data.rewardStr = "$100";
	data.startPosition = toVector3(1522.948, -18.84619, 97.08103);
	data.isTargetMale = true;
	data.targetName = "Carlton Martin";

	return new CarlMartinExecutor(data, areasMgr);
}

TreasuryPeteExecutor* BountyMissionsFactory::treasuryPeteExecutor()
{
	BountyMissionData data;
	data.id = 30;
	data.area = MapAreas::SaintDenis;
	data.missionName = "TreasuryPete";
	data.crime = "Bank Robbery";
	data.description = "Peter Broadwell, was a money laundering crook who\nthought after his sherade was uncovered he could\nmake a final bout by robbing the Saint Denis bank.\nNo money was lost however, several lives were.\nSources claim he waiting for a boat to take him to his\nrefuge with his fellow robbers.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 100;
	data.rewardStr = "$100";
	data.startPosition = toVector3(2856.04, -203.053, 41.1886);
	data.isTargetMale = true;
	data.targetName = "Treasury Pete";

	return new TreasuryPeteExecutor(data, areasMgr);
}

RobertCorbucciExecutor* BountyMissionsFactory::robertCorbucciExecutor()
{
	BountyMissionData data;
	data.id = 31;
	data.area = MapAreas::SaintDenis;
	data.missionName = "RobertCorbucci";
	data.crime = "Murder";
	data.description = "Robert Corbucci is a former associate of Guido Martelli.\nWord on the street is things didn't quite workout between\nhim and the new management. To prevent further street\njustice, the state of Lemoyne has put a bounty\non his head to bring him in dead or alive.";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 105;
	data.rewardStr = "$105";
	data.startPosition = toVector3(1261.292, -419.4841, 95.66013);
	data.isTargetMale = true;
	data.targetName = "Robert Corbucci";

	return new RobertCorbucciExecutor(data, areasMgr);
}

MikeSandersExecutor* BountyMissionsFactory::mikeSandersExecutor()
{
	BountyMissionData data;
	data.id = 32;
	data.area = MapAreas::SaintDenis;
	data.missionName = "LucienVinrouge";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 110;
	data.rewardStr = "$110";
	data.startPosition = toVector3(2315.076, -343.0998, 42.65502);
	data.isTargetMale = true;
	data.targetName = "Lucien le Vinrouge";

	return new MikeSandersExecutor(data, areasMgr);
}

ChrisJaniceExecutor* BountyMissionsFactory::chrisJaniceExecutor()
{
	BountyMissionData data;
	data.id = 33;
	data.area = MapAreas::SaintDenis;
	data.missionName = "ChrisJanice";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 110;
	data.rewardStr = "$110";
	data.startPosition = toVector3(1888.254, 294.222, 76.73746);
	data.isTargetMale = true;
	data.targetName = "Christopher Janice";

	return new ChrisJaniceExecutor(data, areasMgr);
}

JustusBarnesExecutor* BountyMissionsFactory::justusBarnesExecutor()
{
	BountyMissionData data;
	data.id = 34;
	data.area = MapAreas::Strawberry;
	data.missionName = "JustusBarnes";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 60;
	data.rewardStr = "$60";
	data.startPosition = toVector3(-853.949, -750.213, 59.23435);
	data.isTargetMale = true;
	data.targetName = "Justus Barnes";

	return new JustusBarnesExecutor(data, areasMgr);
}

WilliamRogersExecutor* BountyMissionsFactory::williamRogersExecutor()
{
	BountyMissionData data;
	data.id = 35;
	data.area = MapAreas::Strawberry;
	data.missionName = "WilliamRogers";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 55;
	data.rewardStr = "$55";
	data.startPosition = toVector3(-2480.93, -171.0881, 178.6074);
	data.isTargetMale = true;
	data.targetName = "William Rogers";

	return new WilliamRogersExecutor(data, areasMgr);
}

BobLaneExecutor* BountyMissionsFactory::bobLaneExecutor()
{
	BountyMissionData data;
	data.id = 36;
	data.area = MapAreas::Strawberry;
	data.missionName = "BobLane";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 55;
	data.rewardStr = "$55";
	data.startPosition = toVector3(-1873.52, -1112.42, 83.35722);
	data.isTargetMale = true;
	data.targetName = "Bob Lane";

	return new BobLaneExecutor(data, areasMgr);
}

GeorgeCoenExecutor* BountyMissionsFactory::georgeCoenExecutor()
{
	BountyMissionData data;
	data.id = 37;
	data.area = MapAreas::Strawberry;
	data.missionName = "GeorgeCoen";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 65;
	data.rewardStr = "$65";
	data.startPosition = toVector3(-1578.95, 253.227, 111.212);
	data.isTargetMale = true;
	data.targetName = "George Coen";

	return new GeorgeCoenExecutor(data, areasMgr);
}

BuckHicoxExecutor* BountyMissionsFactory::buckHicoxExecutor()
{
	BountyMissionData data;
	data.id = 38;
	data.area = MapAreas::Strawberry;
	data.missionName = "BuckHicox";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 60;
	data.rewardStr = "$60";
	data.startPosition = toVector3(-2125.775, 361.3478, 136.1135);
	data.isTargetMale = true;
	data.targetName = "Buck Hicox";

	return new BuckHicoxExecutor(data, areasMgr);
}

JohnEastwoodExecutor* BountyMissionsFactory::johnEastwoodExecutor()
{
	BountyMissionData data;
	data.id = 39;
	data.area = MapAreas::Strawberry;
	data.missionName = "JohnEastwood";
	data.crime = "Murder";
	data.description = "";
	data.requiredTargetCondition = TargetCondition::DeadOrAlive;
	data.reward = 55;
	data.rewardStr = "$55";
	data.startPosition = toVector3(-1515.187, 717.3212, 125.5926);
	data.isTargetMale = true;
	data.targetName = "John Eastwood";

	return new JohnEastwoodExecutor(data, areasMgr);
}

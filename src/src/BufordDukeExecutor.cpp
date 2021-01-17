#include "Main.h";

using namespace std;

BufordDukeExecutor::BufordDukeExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(100);
	setRequiredDistanceToLocateTarget(75);
	setMustBeCloseToLocate(true);

	campfirePos = toVector3(1585.817, -1851.348, 51.3534);
	enemiesGroup = new GuardsGroup(campfirePos, 25, true); // Create a new Guards Group. First parameter is the center of the defense area. The second one is the radius. The third is whether to tolerate the player when he gets close or not.

	campfire = NULL;
	horse = NULL;
}

void BufordDukeExecutor::update()
{
	BaseMissionExecutor::update();
	releaseUnnecessaryEntities();
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 lastImpactCoords;
	vector<Ped>::iterator pedItr;
	vector<Ped>* enemyPeds = enemiesGroup->peds();
	for (pedItr = enemyPeds->begin(); pedItr != enemyPeds->end(); ++pedItr)
	{
		if (!ENTITY::IS_ENTITY_DEAD(target) && !isPedHogtied(target))
		{
			if (!PED::IS_PED_ON_MOUNT(target) && !PED::_0xAAB0FE202E9FC9F0(horse, -1) && !PED::IS_PED_IN_COMBAT(target, player))
			{
				PED::_0x5337B721C51883A9(*pedItr, true, true);
			}
		}
		if ((ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(*pedItr, player, true, true) || WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(player, &lastImpactCoords) && distanceBetween(ENTITY::GET_ENTITY_COORDS(*pedItr, 1, 0), lastImpactCoords) <= GUARD_SUSPECT_RANGE) && getMissionStage() == BountyMissionStage::LocateTarget)
		{
			nextStage();
		}
	}

	enemiesGroup->update(); // Update the group to keep it working

	if (getMissionStage() == BountyMissionStage::CaptureTarget && !ENTITY::IS_ENTITY_DEAD(target))
	{
		if (distanceBetweenEntities(target, player) > 80)
		{
			showSubtitle("The target is getting too far!");
		}
		if (distanceBetweenEntities(target, player) > 120)
		{
			PED::DELETE_PED(&target);
			PED::DELETE_PED(&horse);
			fail("Bounty failed, target lost");
		}
	}
}

void BufordDukeExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);
	addHorse(horse);
	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(1590.71, -1833.202, 51.35937));
	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(1593.803, -1834.582, 51.36625));

	// Now just add the enemies to the group to make them be controlled by it
	RoutineParams routine1;
	routine1.patrolName = "miss_hello5";
	routine1.patrolRoute.push_back(toVector3(1596.16, -1850.09, 55.2528));
	routine1.patrolHeading.push_back(toVector3(1596.47, -1850.17, 55.2528));
	routine1.patrolRoute.push_back(toVector3(1598.38, -1843.09, 52.3534));
	routine1.patrolHeading.push_back(toVector3(1597.98, -1843.11, 52.3534));
	routine1.patrolRoute.push_back(toVector3(1611.71, -1841.65, 51.9845));
	routine1.patrolHeading.push_back(toVector3(1612.56, -1841.17, 51.7366));
	routine1.patrolRoute.push_back(toVector3(1603.08, -1858.48, 52.3534));
	routine1.patrolHeading.push_back(toVector3(1602.5, -1859.34, 52.3531));

	RoutineParams routine2;
	routine2.patrolName = "miss_hello6";
	routine2.patrolRoute.push_back(toVector3(1582.82, -1856.92, 52.3534));
	routine2.patrolHeading.push_back(toVector3(1583.14, -1856.36, 52.3534));
	routine2.patrolRoute.push_back(toVector3(1572.4, -1845.28, 52.2836));
	routine2.patrolHeading.push_back(toVector3(1571.71, -1844.8, 52.2129));
	routine2.patrolRoute.push_back(toVector3(1562.2, -1864.02, 50.0294));
	routine2.patrolHeading.push_back(toVector3(1561.32, -1864.56, 50.0564));
	routine2.patrolRoute.push_back(toVector3(1582.35, -1873.63, 50.6202));
	routine2.patrolHeading.push_back(toVector3(1582.79, -1874.08, 50.4752));

	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(1587.436, -1847.274, 51.35342), 164), IdlingModifier::Scout);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(1587.88, -1851.641, 51.52284), 72), IdlingModifier::Rest);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(1583.227, -1857.805, 51.3534), (rand() % 361)), IdlingModifier::Patrol, routine2);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(1588.024, -1839.284, 57.53828), 66), IdlingModifier::Scout);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(1585.812, -1845.111, 57.57048), (rand() % 361)), IdlingModifier::Scout);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(1597.018, -1849.776, 54.25288), (rand() % 361)), IdlingModifier::Patrol, routine1);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(1580.818, -1843.372, 51.35342), (rand() % 345 + 153)), IdlingModifier::Scout);
	enemiesGroup->start();
}

Ped BufordDukeExecutor::spawnTarget()
{
	RoutineParams routine3;
	this->horse = createPed("A_C_Horse_KentuckySaddle_Grey", toVector3(1587.518, -1832.286, 51.4919));
	routine3.Horse = horse;
	routine3.isTarget = true;
	Vector3 targetPos = toVector3(1586.68, -1841.879, 51.35339);
	Ped target = createPed("G_M_O_UniExConfeds_01", targetPos, 247);
	enemiesGroup->add(target, IdlingModifier::Rest, routine3);
	return target;
}

void BufordDukeExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	enemiesGroup->addBlips();
}

void BufordDukeExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false);
	horses.push_back(horse);
}

void BufordDukeExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void BufordDukeExecutor::releaseUnnecessaryEntities()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	std::vector<Ped>::iterator it;

	if (getMissionStage() >= BountyMissionStage::ArriveToPoliceStation)
	{
		for (it = horses.begin(); it != horses.end(); it++)
		{
			releaseEntitySafe(&(*it));
		}
	}
}

void BufordDukeExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();

	enemiesGroup->stop();
	releaseEntitySafe(&campfire);

	vector<Ped>::iterator pedItr;
	for (pedItr = horses.begin(); pedItr != horses.end(); pedItr++)
	{
		releaseEntitySafe(&(*pedItr));
	}
	vector<Ped>* enemyPeds = enemiesGroup->peds();
	for (pedItr = enemyPeds->begin(); pedItr != enemyPeds->end(); ++pedItr)
	{
		releaseEntitySafe(&(*pedItr));
	}
}

/*#include "Main.h";

using namespace std;

const int IDLE_DIST = 100;
const int ALERT_DIST = 35;
const int WARN_DIST = 30;
const int HEARING_RANGE = 45;
const int COMBAT_RANGE = 20;

BufordDukeExecutor::BufordDukeExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(100);
	setRequiredDistanceToLocateTarget(50);
	setMustBeCloseToLocate(true);
	enemiesStatus = EnemiesMode::IDLE;
	campfirePos = toVector3(1585.817, -1851.348, 51.3534); //test deze bounty
	toleratePlayer = true;
	campfire = NULL;
	horse = NULL;
	weapon == false;
}

void BufordDukeExecutor::update()
{
	BaseMissionExecutor::update();
	releaseUnnecessaryEntities();
	Ped player = PLAYER::PLAYER_PED_ID();
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	if (getMissionStage() == BountyMissionStage::LocateTarget || getMissionStage() == BountyMissionStage::CaptureTarget)
	{
		float distanceToTarget = distanceBetweenEntities(*pedItr, player);
		switch (enemiesStatus)
		{
		case EnemiesMode::IDLE:
			if (distanceToTarget <= ALERT_DIST)
			{
				if (toleratePlayer)
				{
					stopwatch.start();
					enterAlertMode();
				}
				else
				{
					enterCombatMode();
				}
			}
			break;
		case EnemiesMode::ALERTED:
			if (stopwatch.getElapsedSecondsRealTime() >= 5)
			{
				if (toleratePlayer)
				{
					stopwatch.start();
					enterWarningMode();
				}
				else
				{
					enterCombatMode();
				}
			}
			else if (distanceToTarget >= IDLE_DIST)
			{
				stopwatch.stop();
				enterIdleMode();
			}
			break;

		case EnemiesMode::WARNING:
			if (stopwatch.getElapsedSecondsRealTime() >= 4)
			{
				if (distanceToTarget <= WARN_DIST)
				{
					enterCombatMode();
				}
				else if (distanceToTarget >= ALERT_DIST)
				{
					toleratePlayer = false;
					stopwatch.stop();
					enterAlertMode();
				}
			}
			break;
		}

		if (enemiesStatus < EnemiesMode::COMBAT && distanceToTarget <= HEARING_RANGE)
		{
			if (distanceToTarget <= COMBAT_RANGE || PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()) || PED::IS_PED_SHOOTING(player))
			{
				enterCombatMode();
			}
		}
	}

	if (getMissionStage() == BountyMissionStage::LocateTarget && PED::IS_PED_SHOOTING(player) && enemiesStatus < EnemiesMode::COMBAT)
	{
		enterCombatMode();
	}
	else if (getMissionStage() == BountyMissionStage::CaptureTarget && PED::IS_PED_SHOOTING(player) && enemiesStatus < EnemiesMode::COMBAT)
	{
		enterCombatMode();
	}

	if (getMissionStage() == BountyMissionStage::CaptureTarget && enemiesStatus >= EnemiesMode::ALERTED && !ENTITY::IS_ENTITY_DEAD(target))
	{
		if (distanceBetweenEntities(target, player) > 80)
		{
			showSubtitle("The target is getting too far!");
		}
		if (distanceBetweenEntities(target, player) > 120)
		{
			PED::DELETE_PED(&target);
			fail("Bounty failed, target lost");
		}
	}

}

Ped BufordDukeExecutor::spawnTarget()
{
	Vector3 targetPos = toVector3(1586.68, -1841.879, 52.35339);
	Ped target = createPed("G_M_O_UniExConfeds_01", targetPos);
	return target;
}

void BufordDukeExecutor::enterIdleMode()
{
	char* scenarioName;
	Ped player = PLAYER::PLAYER_PED_ID();
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		Object seq;
		AI::OPEN_SEQUENCE_TASK(&seq);
		AI::TASK_TURN_PED_TO_FACE_COORD(*pedItr, campfirePos.x, campfirePos.y, campfirePos.z, 0);
		AI::CLOSE_SEQUENCE_TASK(seq);
		AI::TASK_PERFORM_SEQUENCE(*pedItr, seq);
		AI::CLEAR_SEQUENCE_TASK(&seq);
	}

	enemiesStatus = EnemiesMode::IDLE;
}

void BufordDukeExecutor::enterAlertMode()
{
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		PED::_0xFE07FF6495D52E2A(*pedItr, 0, 0, 0);
		AI::TASK_TURN_PED_TO_FACE_ENTITY(*pedItr, PLAYER::PLAYER_PED_ID(), -1, 0, 0, 0);
	}

	if (enemiesStatus == EnemiesMode::IDLE)
	{
		playAmbientSpeech(target, "GET_LOST");
	}
	else if (enemiesStatus == EnemiesMode::WARNING)
	{
		playAmbientSpeech(target, "WON_DISPUTE");
	}

	enemiesStatus = EnemiesMode::ALERTED;
}

void BufordDukeExecutor::enterWarningMode()
{
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		weapon == true;
		int iWeapon = rand() % 2 + 1;
		if (iWeapon == 1)
		{
			WEAPON::SET_CURRENT_PED_WEAPON(*pedItr, WEAPON::GET_BEST_PED_WEAPON(*pedItr, 0, 0), true, 0, false, false);
		}
		if (iWeapon == 2)
		{
			giveWeaponToPed(*pedItr, RevolverSchofield, 0x64356159, true);
			WEAPON::REMOVE_WEAPON_FROM_PED(*pedItr, WEAPON::GET_BEST_PED_WEAPON(*pedItr, 0, 0), false, 0);
		}
	}

	playAmbientSpeech(target, "FINAL_WARNING");
	enemiesStatus = EnemiesMode::WARNING;
}

void BufordDukeExecutor::enterCombatMode()
{
	enemiesStatus = EnemiesMode::COMBAT;

	Ped player = PLAYER::PLAYER_PED_ID();
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		PED::_0xFE07FF6495D52E2A(*pedItr, 0, 0, 0);
		if (weapon == false) 
		{
			int iWeapon = rand() % 2 + 1;
			if (iWeapon == 1)
			{
				WEAPON::SET_CURRENT_PED_WEAPON(*pedItr, WEAPON::GET_BEST_PED_WEAPON(*pedItr, 0, 0), true, 0, false, false);
			}
			if (iWeapon == 2)
			{
				giveWeaponToPed(*pedItr, RevolverSchofield, 0x64356159, true);
				WEAPON::REMOVE_WEAPON_FROM_PED(*pedItr, WEAPON::GET_BEST_PED_WEAPON(*pedItr, 0, 0), false, 0);
			}
		}
		if (*pedItr == target)
		{
			int iSecret = rand() % 2 + 1;
			if (iSecret == 1)
			{

				Object seq;
				AI::OPEN_SEQUENCE_TASK(&seq);
				AI::_0x92DB0739813C5186(0, horse, -1, -1, 2.0f, 1, 0, 0); // Mount the horse
				AI::_0xFD45175A6DFD7CE9(0, player, 3, 0, -999.0f, -1, 0); // FLEE
				AI::CLOSE_SEQUENCE_TASK(seq);

				AI::CLEAR_PED_TASKS(target, 1, 1);
				AI::TASK_PERFORM_SEQUENCE(target, seq);
				AI::CLEAR_SEQUENCE_TASK(&seq);
				playAmbientSpeech(target, "ITS_MALE_EXTREME");
			}
			else if (iSecret == 2)
			{
				Object seq;
				AI::OPEN_SEQUENCE_TASK(&seq);
				AI::TASK_COMBAT_PED(target, player, 0, 16);
				AI::CLOSE_SEQUENCE_TASK(seq);

				AI::CLEAR_PED_TASKS(target, 1, 1);
				AI::TASK_PERFORM_SEQUENCE(target, seq);
				AI::CLEAR_SEQUENCE_TASK(&seq);
				playAmbientSpeech(target, "ITS_MALE_EXTREME");
			}
		}
		else
		{
			Object seq;
			AI::OPEN_SEQUENCE_TASK(&seq);
			AI::TASK_COMBAT_PED(0, player, 0, 16);
			AI::CLOSE_SEQUENCE_TASK(seq);
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(*pedItr, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
			AI::CLEAR_PED_TASKS(*pedItr, 1, 1);
			AI::TASK_PERFORM_SEQUENCE(*pedItr, seq);
			AI::CLEAR_SEQUENCE_TASK(&seq);
		}
	}
}

void BufordDukeExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);

	this->horse = createPed("A_C_Horse_Turkoman_Gold", toVector3(1587.518, -1832.286, 52.4919));
	addHorse(horse);
	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(1590.71, -1833.202, 52.35937));
	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(1593.803, -1834.582, 52.36625));

	addEnemy(target);
	addEnemy(toVector3(1587.436, -1847.274, 52.35342));
	addEnemy(toVector3(1587.88, -1851.641, 52.52284));
	addEnemy(toVector3(1583.227, -1857.805, 52.3534));
	addEnemy(toVector3(1588.024, -1839.284, 58.53828));
	addEnemy(toVector3(1585.812, -1845.111, 58.57048));
	addEnemy(toVector3(1597.018, -1849.776, 55.25288));
	addEnemy(toVector3(1580.818, -1843.372, 52.35342));

	enterIdleMode();
}

void BufordDukeExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();

	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		if (*pedItr != target)
		{
			createBlip(*pedItr, BLIP_STYLE_ENEMY);
		}
	}
}

void BufordDukeExecutor::createEnemyBlips()
{
	std::vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (*it != target)
		{
			createBlip(*it, BLIP_STYLE_ENEMY);
		}
	}
}

void BufordDukeExecutor::releaseUnnecessaryEntities()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	std::vector<Ped>::iterator it;

	if (getMissionStage() >= BountyMissionStage::ArriveToPoliceStation)
	{
		releaseEntitySafe(&horse);

		for (it = enemies.begin(); it != enemies.end(); ++it)
		{
			if (distanceBetweenEntities(*it, player) > 250 ||  ENTITY::IS_ENTITY_DEAD(*it))
			{
				releaseEntitySafe(&(*it));
			}
		}
	}
}

void BufordDukeExecutor::addEnemy(Vector3 pos)
{
	Ped enemyPed = createPed("G_M_Y_UniExConfeds_01", pos);
	addEnemy(enemyPed);
}

void BufordDukeExecutor::addEnemy(Ped ped)
{
	enemies.push_back(ped);

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
	AI::CLEAR_PED_TASKS(ped, true, true);
}

void BufordDukeExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void BufordDukeExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false); // give saddle
	horses.push_back(horse);
}

void BufordDukeExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();
	releaseEntitySafe(&campfire);

	vector<Ped>::iterator pedItr;
	for (pedItr = horses.begin(); pedItr != horses.end(); pedItr++)
	{
		releaseEntitySafe(&(*pedItr));
	}

	for (pedItr = enemies.begin(); pedItr != enemies.end(); ++pedItr)
	{
		releaseEntitySafe(&(*pedItr));
	}
}*/
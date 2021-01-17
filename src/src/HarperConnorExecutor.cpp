#include "Main.h";

using namespace std;

HarperConnorExecutor::HarperConnorExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(100);
	setRequiredDistanceToLocateTarget(75);
	setMustBeCloseToLocate(true);

	campfirePos = toVector3(768.0861, -852.4528, 54.38295);
	enemiesGroup = new GuardsGroup(campfirePos, 25, true); // Create a new Guards Group. First parameter is the center of the defense area. The second one is the radius. The third is whether to tolerate the player when he gets close or not.

	campfire = NULL;
	horse = NULL;
}

void HarperConnorExecutor::update()
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

void HarperConnorExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);
	addHorse(horse);
	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(758.0254, -862.0231, 53.66626));
	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(761.9842, -862.2714, 53.74209));

	// Now just add the enemies to the group to make them be controlled by it
	RoutineParams routine1;
	routine1.patrolName = "miss_hello7";
	routine1.patrolRoute.push_back(toVector3(769.776, -835.057, 55.7592));
	routine1.patrolHeading.push_back(toVector3(769.352, -833.85, 55.7819));
	routine1.patrolRoute.push_back(toVector3(777.94, -850.234, 55.194));
	routine1.patrolHeading.push_back(toVector3(778.152, -849.588, 55.1907));
	routine1.patrolRoute.push_back(toVector3(773.842, -861.309, 54.2665));
	routine1.patrolHeading.push_back(toVector3(773.229, -861.963, 54.2096));

	RoutineParams routine2;
	routine2.patrolName = "miss_hello8";
	routine2.patrolRoute.push_back(toVector3(753.386, -844.66, 55.1289));
	routine2.patrolHeading.push_back(toVector3(753.514, -844.66, 55.1268));
	routine2.patrolRoute.push_back(toVector3(751.576, -859.582, 54.4967));
	routine2.patrolHeading.push_back(toVector3(751.411, -860.135, 54.3287));
	routine2.patrolRoute.push_back(toVector3(764.514, -859.939, 55.035));
	routine2.patrolHeading.push_back(toVector3(764.994, -860.007, 54.9913));
	routine2.patrolRoute.push_back(toVector3(750.397, -857.654, 54.5683));
	routine2.patrolHeading.push_back(toVector3(749.73, -857.485, 54.4517));

	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(762.6347, -850.3631, 54.25639), 245), IdlingModifier::Rest);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(762.7381, -853.0121, 54.34014), 286), IdlingModifier::Rest);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(765.1423, -856.9935, 54.24311), 326), IdlingModifier::Rest);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(769.776, -835.057, 54.7592), (rand() % 361)), IdlingModifier::Patrol, routine1);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(776.5958, -844.3274, 54.55535), (rand() % 361)), IdlingModifier::Scout);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(757.3467, -844.9959, 54.13348), (rand() % 274 + 98)), IdlingModifier::Scout);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(754.035, -844.9783, 54.15492), (rand() % 361)), IdlingModifier::Patrol, routine2);
	enemiesGroup->start();
}

Ped HarperConnorExecutor::spawnTarget()
{
	RoutineParams routine3;
	this->horse = createPed("A_C_Horse_KentuckySaddle_Grey", toVector3(755.3113, -861.9045, 53.51758));
	routine3.Horse = horse;
	routine3.isTarget = true;
	Vector3 targetPos = toVector3(764.5617, -842.8209, 54.50637);
	Ped target = createPed("G_M_O_UniExConfeds_01", targetPos, (rand() % 269 + 82));
	enemiesGroup->add(target, IdlingModifier::Rest, routine3);
	return target;
}

void HarperConnorExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	enemiesGroup->addBlips();
}

void HarperConnorExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false);
	horses.push_back(horse);
}

void HarperConnorExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void HarperConnorExecutor::releaseUnnecessaryEntities()
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

void HarperConnorExecutor::cleanup()
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

HarperConnorExecutor::HarperConnorExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(100);
	setRequiredDistanceToLocateTarget(50);
	setMustBeCloseToLocate(true);
	enemiesStatus = EnemiesMode::IDLE;
	campfirePos = toVector3(768.0861, -852.4528, 54.38295); //test deze bounty
	toleratePlayer = true;
	campfire = NULL;
	horse = NULL;
	weapon == false;
}

void HarperConnorExecutor::update()
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

Ped HarperConnorExecutor::spawnTarget()
{
	Vector3 targetPos = toVector3(764.5617, -842.8209, 55.50637);
	Ped target = createPed("G_M_O_UniExConfeds_01", targetPos);
	return target;
}

void HarperConnorExecutor::enterIdleMode()
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

void HarperConnorExecutor::enterAlertMode()
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

void HarperConnorExecutor::enterWarningMode()
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

void HarperConnorExecutor::enterCombatMode()
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

void HarperConnorExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);

	this->horse = createPed("A_C_Horse_Turkoman_Gold", toVector3(755.3113, -861.9045, 54.51758));
	addHorse(horse);
	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(758.0254, -862.0231, 54.66626));
	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(761.9842, -862.2714, 54.74209));

	addEnemy(target);
	addEnemy(toVector3(762.6347, -850.3631, 55.25639));
	addEnemy(toVector3(762.7381, -853.0121, 55.34014));
	addEnemy(toVector3(765.1423, -856.9935, 55.24311));
	addEnemy(toVector3(779.6448, -844.4714, 55.53098));
	addEnemy(toVector3(776.5958, -844.3274, 55.55535));
	addEnemy(toVector3(757.3467, -844.9959, 55.13348));
	addEnemy(toVector3(754.035, -844.9783, 55.15492));

	enterIdleMode();
}

void HarperConnorExecutor::onTargetLocated()
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

void HarperConnorExecutor::createEnemyBlips()
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

void HarperConnorExecutor::releaseUnnecessaryEntities()
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

void HarperConnorExecutor::addEnemy(Vector3 pos)
{
	Ped enemyPed = createPed("G_M_Y_UniExConfeds_02", pos);
	addEnemy(enemyPed);
}

void HarperConnorExecutor::addEnemy(Ped ped)
{
	enemies.push_back(ped);

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
	AI::CLEAR_PED_TASKS(ped, true, true);
}

void HarperConnorExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void HarperConnorExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false); // give saddle
	horses.push_back(horse);
}

void HarperConnorExecutor::cleanup()
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
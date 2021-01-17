#include "Main.h";

using namespace std;

EmmettDavisExecutor::EmmettDavisExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(100);
	setRequiredDistanceToLocateTarget(60);
	setMustBeCloseToLocate(true);

	campfirePos = toVector3(718.9932, -464.4996, 78.51635);
	enemiesGroup = new GuardsGroup(campfirePos, 25, true); // Create a new Guards Group. First parameter is the center of the defense area. The second one is the radius. The third is whether to tolerate the player when he gets close or not.

	campfire = NULL;
	horse = NULL;
}

void EmmettDavisExecutor::update()
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

void EmmettDavisExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);
	addHorse(horse);
	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(721.1486, -454.9473, 79.12532));
	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(718.6625, -453.2034, 79.62189));

	// Now just add the enemies to the group to make them be controlled by it

	RoutineParams routine2;
	routine2.patrolName = "miss_hello10";
	routine2.patrolRoute.push_back(toVector3(727.697, -475.662, 76.6961));
	routine2.patrolHeading.push_back(toVector3(727.842, -476.197, 76.5846));
	routine2.patrolRoute.push_back(toVector3(741.568, -465.869, 77.5322));
	routine2.patrolHeading.push_back(toVector3(742.134, -465.27, 77.6283));
	routine2.patrolRoute.push_back(toVector3(739.266, -480.513, 76.5501));
	routine2.patrolHeading.push_back(toVector3(739.062, -481.139, 76.509));
	routine2.patrolRoute.push_back(toVector3(717.709, -471.985, 78.9106));
	routine2.patrolHeading.push_back(toVector3(717.826, -471.583, 78.957));

	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(724.744, -462.2702, 78.33641), 44), IdlingModifier::Rest);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(726.2008, -460.0238, 78.21921), 52), IdlingModifier::Rest);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(723.8654, -467.3318, 78.89738), 57), IdlingModifier::Scout);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(720.4483, -470.2119, 78.00019), (rand() % 361)), IdlingModifier::Scout);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(717.4052, -467.7865, 78.4699), 335), IdlingModifier::Rest);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(724.9504, -469.1515, 84.89081), (rand() % 361)), IdlingModifier::Rest);
	enemiesGroup->add(createPed("G_M_Y_UniExConfeds_01", toVector3(728.2208, -475.3792, 75.7203), (rand() % 361)), IdlingModifier::Patrol, routine2);
	enemiesGroup->start();
}

Ped EmmettDavisExecutor::spawnTarget()
{
	RoutineParams routine3;
	this->horse = createPed("A_C_Horse_KentuckySaddle_Grey", toVector3(722.8624, -456.423, 78.72858));
	routine3.Horse = horse;
	routine3.isTarget = true;
	routine3.patrolName = "miss_bandito12";
	routine3.patrolRoute.push_back(toVector3(732.757, -461.006, 79.4191));
	routine3.patrolHeading.push_back(toVector3(733.127, -461.309, 79.4613));
	routine3.patrolRoute.push_back(toVector3(724.289, -455.323, 79.9256));
	routine3.patrolHeading.push_back(toVector3(723.792, -455.157, 79.98));
	routine3.patrolRoute.push_back(toVector3(730.98, -452.908, 82.8652));
	routine3.patrolHeading.push_back(toVector3(730.902, -451.422, 82.687));
	routine3.patrolRoute.push_back(toVector3(739.546, -457.167, 81.8912));
	routine3.patrolHeading.push_back(toVector3(739.823, -457.334, 81.8891));
	Vector3 targetPos = toVector3(734.3577, -461.5699, 78.50893);
	Ped target = createPed("G_M_O_UniExConfeds_01", targetPos, (rand() % 361));
	enemiesGroup->add(target, IdlingModifier::Patrol, routine3);
	return target;
}

void EmmettDavisExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	enemiesGroup->addBlips();
}

void EmmettDavisExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false);
	horses.push_back(horse);
}

void EmmettDavisExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void EmmettDavisExecutor::releaseUnnecessaryEntities()
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

void EmmettDavisExecutor::cleanup()
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

EmmettDavisExecutor::EmmettDavisExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(100);
	setRequiredDistanceToLocateTarget(50);
	setMustBeCloseToLocate(true);
	enemiesStatus = EnemiesMode::IDLE;
	campfirePos = toVector3(718.9932, -464.4996, 78.51635); //test deze bounty
	toleratePlayer = true;
	campfire = NULL;
	horse = NULL;
	weapon == false;
}

void EmmettDavisExecutor::update()
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

Ped EmmettDavisExecutor::spawnTarget()
{
	Vector3 targetPos = toVector3(734.3577, -461.5699, 79.50893);
	Ped target = createPed("G_M_O_UniExConfeds_01", targetPos);
	return target;
}

void EmmettDavisExecutor::enterIdleMode()
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

void EmmettDavisExecutor::enterAlertMode()
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

void EmmettDavisExecutor::enterWarningMode()
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

void EmmettDavisExecutor::enterCombatMode()
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

void EmmettDavisExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);

	this->horse = createPed("A_C_Horse_Turkoman_Gold", toVector3(722.8624, -456.423, 79.72858));
	addHorse(horse);
	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(721.1486, -454.9473, 80.12532));
	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(718.6625, -453.2034, 80.62189));

	addEnemy(target);
	addEnemy(toVector3(724.744, -462.2702, 79.33641));
	addEnemy(toVector3(726.2008, -460.0238, 79.21921));
	addEnemy(toVector3(723.8654, -467.3318, 79.89738));
	addEnemy(toVector3(720.4483, -470.2119, 79.00019));
	addEnemy(toVector3(717.4052, -467.7865, 79.4699));
	addEnemy(toVector3(724.9504, -469.1515, 85.89081));
	addEnemy(toVector3(728.2208, -475.3792, 76.7203));

	enterIdleMode();
}

void EmmettDavisExecutor::onTargetLocated()
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

void EmmettDavisExecutor::createEnemyBlips()
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

void EmmettDavisExecutor::releaseUnnecessaryEntities()
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

void EmmettDavisExecutor::addEnemy(Vector3 pos)
{
	Ped enemyPed = createPed("G_M_Y_UniExConfeds_02", pos);
	addEnemy(enemyPed);
}

void EmmettDavisExecutor::addEnemy(Ped ped)
{
	enemies.push_back(ped);

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
	AI::CLEAR_PED_TASKS(ped, true, true);
}

void EmmettDavisExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void EmmettDavisExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false); // give saddle
	horses.push_back(horse);
}

void EmmettDavisExecutor::cleanup()
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
#include "Main.h";

using namespace std;

JesseHillExecutor::JesseHillExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(130);
	setRequiredDistanceToLocateTarget(50);
	setMustBeCloseToLocate(true);

	campfirePos = toVector3(-5705.996, -2390.512, 4.240256);
	enemiesGroup = new GuardsGroup(campfirePos, 25, true); // Create a new Guards Group. First parameter is the center of the defense area. The second one is the radius. The third is whether to tolerate the player when he gets close or not.

	campfire = NULL;
	horse = NULL;
}

void JesseHillExecutor::update()
{
	BaseMissionExecutor::update();
	releaseUnnecessaryEntities();
	Ped player = PLAYER::PLAYER_PED_ID();

	enemiesGroup->update(); // Update the group to keep it working

	if (getMissionStage() == BountyMissionStage::CaptureTarget && !ENTITY::IS_ENTITY_DEAD(target))
	{
		if (distanceBetweenEntities(target, player) > 80)
		{
			showSubtitle("The target is getting too far!");
		}
		if (distanceBetweenEntities(target, player) > 120)
		{
			fail("Bounty failed, target lost");
		}
	}
}

void JesseHillExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);

	this->horse = createPed("A_C_Horse_Turkoman_Gold", toVector3(-5695.089, -2379.958, 4.456663));
	addHorse(horse);
	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(-5693.293, -2376.194, 5.328225));
	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(-5687.966, -2379.522, 3.616471));

	// Now just add the enemies to the group to make them be controlled by it
	enemiesGroup->add(createPed("G_M_M_UniBanditos_01", toVector3(-5711.004, -2391.769, 6.44563))); 
	enemiesGroup->add(createPed("G_M_M_UniBanditos_01", toVector3(-5706.604, -2387.53, 5.327281)));
	enemiesGroup->add(createPed("G_M_M_UniBanditos_01", toVector3(-5701.083, -2383.894, 4.922241)));
	enemiesGroup->add(createPed("G_M_M_UniBanditos_01", toVector3(-5698.187, -2389.69, 3.816682)));
	enemiesGroup->add(createPed("G_M_M_UniBanditos_01", toVector3(-5704.169, -2405.032, 4.893043)));
	enemiesGroup->add(createPed("G_M_M_UniBanditos_01", toVector3(-5687.943, -2381.427, 3.032831)));
	enemiesGroup->add(createPed("G_M_M_UniBanditos_01", toVector3(-5685.831, -2386.835, 2.014514)));
	enemiesGroup->start();

}

Ped JesseHillExecutor::spawnTarget()
{
	Vector3 targetPos = toVector3(-5710.177, -2386.995, 6.257581);
	Ped target = createPed(M_BOUNTY_TARGET, targetPos);
	enemiesGroup->add(target);
	return target;
}

void JesseHillExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	enemiesGroup->addBlips();
}

void JesseHillExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false);
	horses.push_back(horse);
}

void JesseHillExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void JesseHillExecutor::releaseUnnecessaryEntities()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	std::vector<Ped>::iterator it;

	if (getMissionStage() >= BountyMissionStage::ArriveToPoliceStation)
	{
		releaseEntitySafe(&horse);
	}
}

void JesseHillExecutor::cleanup()
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
	
	delete enemiesGroup;
}

//#include "Main.h";
//
//using namespace std;
//
//const int IDLE_DIST = 45;
//const int ALERT_DIST = 35;
//const int WARN_DIST = 30;
//const int HEARING_RANGE = 45;
//const int COMBAT_RANGE = 12;
//
//JesseHillExecutor::JesseHillExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
//	: BaseMissionExecutor(missionData, areasMgr)
//{
//	setTargetAreaRadius(130);
//	setRequiredDistanceToLocateTarget(50);
//	setMustBeCloseToLocate(true);
//	enemiesStatus = EnemiesMode::IDLE;
//	campfirePos = toVector3(-5705.996, -2390.512, 4.240256);
//	toleratePlayer = true;
//	campfire = NULL;
//	horse = NULL;
//}
//
//void JesseHillExecutor::update()
//{
//	BaseMissionExecutor::update();
//	releaseUnnecessaryEntities();
//	Ped player = PLAYER::PLAYER_PED_ID();
//	if (getMissionStage() == BountyMissionStage::CaptureTarget)
//	{
//		float distanceToTarget = distanceBetweenEntities(target, player);
//		switch (enemiesStatus)
//		{
//		case EnemiesMode::IDLE:
//			if (distanceToTarget <= ALERT_DIST)
//			{
//				if (toleratePlayer)
//				{
//					stopwatch.start();
//					enterAlertMode();
//				}
//				else
//				{
//					enterCombatMode();
//				}
//			}
//			break;
//		case EnemiesMode::ALERTED:
//			if (stopwatch.getElapsedSecondsRealTime() >= 5)
//			{
//				if (toleratePlayer)
//				{
//					stopwatch.start();
//					enterWarningMode();
//				}
//				else
//				{
//					enterCombatMode();
//				}
//			}
//			else if (distanceToTarget >= IDLE_DIST)
//			{
//				stopwatch.stop();
//				enterIdleMode();
//			}
//			break;
//
//		case EnemiesMode::WARNING:
//			if (stopwatch.getElapsedSecondsRealTime() >= 4)
//			{
//				if (distanceToTarget <= WARN_DIST)
//				{
//					enterCombatMode();
//				}
//				else if (distanceToTarget >= ALERT_DIST)
//				{
//					toleratePlayer = false;
//					stopwatch.stop();
//					enterAlertMode();
//				}
//			}
//			break;
//		}
//
//		if (enemiesStatus < EnemiesMode::COMBAT && distanceToTarget <= HEARING_RANGE)
//		{
//			if (distanceToTarget <= COMBAT_RANGE || PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()) || PED::IS_PED_SHOOTING(player))
//			{
//				enterCombatMode();
//			}
//		}
//	}
//
//	if (getMissionStage() == BountyMissionStage::LocateTarget && PED::IS_PED_SHOOTING(player) && enemiesStatus < EnemiesMode::COMBAT)
//	{
//		enterCombatMode();
//	}
//	else if (getMissionStage() == BountyMissionStage::CaptureTarget && PED::IS_PED_SHOOTING(player) && enemiesStatus < EnemiesMode::COMBAT)
//	{
//		enterCombatMode();
//	}
//
//	if (getMissionStage() == BountyMissionStage::CaptureTarget && enemiesStatus >= EnemiesMode::ALERTED && !ENTITY::IS_ENTITY_DEAD(target))
//	{
//		if (distanceBetweenEntities(target, player) > 80)
//		{
//			showSubtitle("The target is getting too far!");
//		}
//		if (distanceBetweenEntities(target, player) > 120)
//		{
//			fail("Bounty failed, target lost");
//		}
//	}
//
//}
//
//Ped JesseHillExecutor::spawnTarget()
//{
//	Vector3 targetPos = toVector3(-5710.177, -2386.995, 6.257581);
//	Ped target = createPed(M_BOUNTY_TARGET, targetPos);
//	return target;
//}
//
//void JesseHillExecutor::enterIdleMode()
//{
//	char* scenarioName;
//	Ped player = PLAYER::PLAYER_PED_ID();
//	vector<Ped>::iterator pedItr;
//	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
//	{
//		Object seq;
//		AI::OPEN_SEQUENCE_TASK(&seq);
//		AI::TASK_TURN_PED_TO_FACE_COORD(*pedItr, campfirePos.x, campfirePos.y, campfirePos.z, 0);
//		AI::CLOSE_SEQUENCE_TASK(seq);
//		AI::TASK_PERFORM_SEQUENCE(*pedItr, seq);
//	}
//
//	enemiesStatus = EnemiesMode::IDLE;
//}
//
//void JesseHillExecutor::enterAlertMode()
//{
//	vector<Ped>::iterator pedItr;
//	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
//	{
//		PED::_0xFE07FF6495D52E2A(*pedItr, 0, 0, 0);
//		AI::TASK_TURN_PED_TO_FACE_ENTITY(*pedItr, PLAYER::PLAYER_PED_ID(), -1, 0, 0, 0);
//	}
//
//	if (enemiesStatus == EnemiesMode::IDLE)
//	{
//		playAmbientSpeech(target, "GET_LOST");
//	}
//	else if (enemiesStatus == EnemiesMode::WARNING)
//	{
//		playAmbientSpeech(target, "WON_DISPUTE");
//	}
//
//	enemiesStatus = EnemiesMode::ALERTED;
//}
//
//void JesseHillExecutor::enterWarningMode()
//{
//	vector<Ped>::iterator pedItr;
//	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
//	{
//		pedEquipBestWeapon(*pedItr);
//	}
//
//	playAmbientSpeech(target, "FINAL_WARNING");
//	enemiesStatus = EnemiesMode::WARNING;
//}
//
//void JesseHillExecutor::enterCombatMode()
//{
//	enemiesStatus = EnemiesMode::COMBAT;
//
//	Ped player = PLAYER::PLAYER_PED_ID();
//	vector<Ped>::iterator pedItr;
//	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
//	{
//		PED::_0xFE07FF6495D52E2A(*pedItr, 0, 0, 0);
//		WEAPON::SET_CURRENT_PED_WEAPON(*pedItr, WEAPON::GET_BEST_PED_WEAPON(*pedItr, 0, 0), true, 0, false, false);
//
//		if (*pedItr == target)
//		{
//			int iSecret;
//			iSecret = rand() % 2 + 1;
//			if (iSecret == 1)
//			{
//
//				Object seq;
//				AI::OPEN_SEQUENCE_TASK(&seq);
//				AI::_0x92DB0739813C5186(0, horse, -1, -1, 2.0f, 1, 0, 0); // Mount the horse
//				AI::_0xFD45175A6DFD7CE9(0, player, 3, 0, -999.0f, -1, 0); // FLEE
//				AI::CLOSE_SEQUENCE_TASK(seq);
//
//				AI::CLEAR_PED_TASKS(target, 1, 1);
//				AI::TASK_PERFORM_SEQUENCE(target, seq);
//				playAmbientSpeech(target, "ITS_MALE_EXTREME");
//			}
//			else if (iSecret == 2)
//			{
//				Object seq;
//				AI::OPEN_SEQUENCE_TASK(&seq);
//				AI::TASK_COMBAT_PED(target, player, 0, 16);
//				AI::CLOSE_SEQUENCE_TASK(seq);
//
//				AI::CLEAR_PED_TASKS(target, 1, 1);
//				AI::TASK_PERFORM_SEQUENCE(target, seq);
//				playAmbientSpeech(target, "ITS_MALE_EXTREME");
//			}
//		}
//		else
//		{
//			Object seq;
//			AI::OPEN_SEQUENCE_TASK(&seq);
//			AI::TASK_COMBAT_PED(0, player, 0, 16);
//			AI::CLOSE_SEQUENCE_TASK(seq);
//
//			AI::CLEAR_PED_TASKS(*pedItr, 1, 1);
//			AI::TASK_PERFORM_SEQUENCE(*pedItr, seq);
//		}
//	}
//}
//
//void JesseHillExecutor::prepareSet()
//{
//	campfire = createProp("P_CAMPFIRE02X", campfirePos);
//
//	this->horse = createPed("A_C_Horse_Turkoman_Gold", toVector3(-5695.089, -2379.958, 4.456663));
//	addHorse(horse);
//	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(-5693.293, -2376.194, 5.328225));
//	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(-5687.966, -2379.522, 3.616471));
//
//	addEnemy(target);
//	addEnemy(toVector3(-5711.004, -2391.769, 6.44563));
//	addEnemy(toVector3(-5706.604, -2387.53, 5.327281));
//	addEnemy(toVector3(-5701.083, -2383.894, 4.922241));
//	addEnemy(toVector3(-5698.187, -2389.69, 3.816682));
//	addEnemy(toVector3(-5704.169, -2405.032, 4.893043));
//	addEnemy(toVector3(-5687.943, -2381.427, 3.032831));
//	addEnemy(toVector3(-5685.831, -2386.835, 2.014514));
//
//	enterIdleMode();
//}
//
//void JesseHillExecutor::onTargetLocated()
//{
//	BaseMissionExecutor::onTargetLocated();
//
//	vector<Ped>::iterator pedItr;
//	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
//	{
//		if (*pedItr != target)
//		{
//			createBlip(*pedItr, BLIP_STYLE_ENEMY);
//		}
//	}
//}
//
//void JesseHillExecutor::createEnemyBlips()
//{
//	std::vector<Ped>::iterator it;
//	for (it = enemies.begin(); it != enemies.end(); ++it)
//	{
//		if (*it != target)
//		{
//			createBlip(*it, BLIP_STYLE_ENEMY);
//		}
//	}
//}
//
//void JesseHillExecutor::releaseUnnecessaryEntities()
//{
//	Ped player = PLAYER::PLAYER_PED_ID();
//	std::vector<Ped>::iterator it;
//
//	if (getMissionStage() >= BountyMissionStage::ArriveToPoliceStation)
//	{
//		releaseEntitySafe(&horse);
//
//		for (it = enemies.begin(); it != enemies.end(); ++it)
//		{
//			if (distanceBetweenEntities(*it, player) > 250 ||  ENTITY::IS_ENTITY_DEAD(*it))
//			{
//				releaseEntitySafe(&(*it));
//			}
//		}
//	}
//}
//
//void JesseHillExecutor::addEnemy(Vector3 pos)
//{
//	Ped enemyPed = createPed("G_M_M_UniBanditos_01", pos);
//	addEnemy(enemyPed);
//}
//
//void JesseHillExecutor::addEnemy(Ped ped)
//{
//	enemies.push_back(ped);
//
//	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
//	AI::CLEAR_PED_TASKS(ped, true, true);
//}
//
//void JesseHillExecutor::addHorse(const char* model, Vector3 pos)
//{
//	Ped horse = createPed((char*)model, pos);
//	addHorse(horse);
//}
//
//void JesseHillExecutor::addHorse(Ped horse)
//{
//	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
//	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false); // give saddle
//	horses.push_back(horse);
//}
//
//void JesseHillExecutor::cleanup()
//{
//	BaseMissionExecutor::cleanup();
//	releaseEntitySafe(&campfire);
//
//	vector<Ped>::iterator pedItr;
//	for (pedItr = horses.begin(); pedItr != horses.end(); pedItr++)
//	{
//		releaseEntitySafe(&(*pedItr));
//	}
//
//	for (pedItr = enemies.begin(); pedItr != enemies.end(); ++pedItr)
//	{
//		releaseEntitySafe(&(*pedItr));
//	}
//}
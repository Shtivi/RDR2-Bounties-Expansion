#include "Main.h";

using namespace std;

const int IDLE_DIST = 0;
const int ALERT_DIST = 0;
const int WARN_DIST = 0;
const int HEARING_RANGE = 0;
const int COMBAT_RANGE = 0;

ChesterBurnettExecutor::ChesterBurnettExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(50);
	setRequiredDistanceToLocateTarget(0);
	setMustBeCloseToLocate(true);
	enemiesStatus = EnemiesMode::IDLE;
	campfirePos = toVector3(-1352.869, 2440.57, 307.4282);
	toleratePlayer = true;
	campfire = NULL;
	horse = NULL;
}

void ChesterBurnettExecutor::update()
{
	BaseMissionExecutor::update();
	releaseUnnecessaryEntities();
	Ped player = PLAYER::PLAYER_PED_ID();
	if (getMissionStage() == BountyMissionStage::CaptureTarget)
	{
		float distanceToTarget = distanceBetweenEntities(target, player);
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
	}
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		if (*pedItr != target)
		{
			if (getMissionStage() == BountyMissionStage::LocateTarget && ENTITY::IS_ENTITY_DEAD(*pedItr) && enemiesStatus < EnemiesMode::COMBAT)
			{
				showSubtitle("Bounty Failed, you killed an innocent man.");
				stopwatch.start();
				enterCombatMode();
				AI::_0xFD45175A6DFD7CE9(target, player, 3, 0, -999.0f, -1, 0); // FLEE
			}
			if (getMissionStage() == BountyMissionStage::ArriveToPoliceStation && ENTITY::IS_ENTITY_DEAD(*pedItr) && distanceBetweenEntities(*pedItr, player) <= 250)
			{
				showSubtitle("Bounty Failed, you killed an innocent man.");
				stopwatch.start();
				enterCombatMode();
				AI::_0xFD45175A6DFD7CE9(target, player, 3, 0, -999.0f, -1, 0); // FLEE
			}
			if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(*pedItr, player, false, false))
			{
				AI::TASK_COMBAT_PED(*pedItr, player, 0, 16);
			}
			if (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(PLAYER::PLAYER_ID(), *pedItr))
			{
				AI::TASK_COWER(*pedItr, 9999, 0, 0);
				if (ENTITY::IS_ENTITY_DEAD(target))
				{
					AI::TASK_COWER(*pedItr, 9999, 0, 0);
				}
			}
		}
		else
		{
			if (ENTITY::IS_ENTITY_DEAD(*pedItr))
			{
				setMustBeCloseToLocate(false);
			}
			if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(*pedItr, player, false, false))
			{
				AI::TASK_COMBAT_PED(*pedItr, player, 0, 16);
			}
			if (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(PLAYER::PLAYER_ID(), *pedItr))
			{
				giveWeaponToPed(target, RevolverCattleman, 0x64356159, true);
				AI::TASK_COMBAT_PED(*pedItr, player, 0, 16);
			}
		}
		if (PED::IS_PED_SHOOTING(player))
		{
			AI::TASK_COWER(*pedItr, 9999, 0, 0);
		}
		if (isPedHogtied(target))
		{
			setMustBeCloseToLocate(false);
		}
	}

	if (getMissionStage() == BountyMissionStage::CaptureTarget && enemiesStatus >= EnemiesMode::ALERTED && !ENTITY::IS_ENTITY_DEAD(target))
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

Ped ChesterBurnettExecutor::spawnTarget()
{
	Vector3 targetPos = toVector3(-1349.408, 2446.22, 308.4254);
	Ped target = createPed("G_M_M_UNIMICAHGOONS_01", targetPos);
	giveWeaponToPed(target, RevolverCattleman, 0x64356159, false);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(target, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
	return target;
}

void ChesterBurnettExecutor::enterIdleMode()
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
	}

	enemiesStatus = EnemiesMode::IDLE;
}

void ChesterBurnettExecutor::enterAlertMode()
{
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		PED::_0xFE07FF6495D52E2A(*pedItr, 0, 0, 0);
	}

	//if (enemiesStatus == EnemiesMode::IDLE)
	{
		playAmbientSpeech(target, "GET_LOST");
	}
	//else if (enemiesStatus == EnemiesMode::WARNING)
	{
		playAmbientSpeech(target, "WON_DISPUTE");
	}

	enemiesStatus = EnemiesMode::ALERTED;
}

void ChesterBurnettExecutor::enterWarningMode()
{
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		pedEquipBestWeapon(*pedItr);
	}

	playAmbientSpeech(target, "FINAL_WARNING");
	enemiesStatus = EnemiesMode::WARNING;
}

void ChesterBurnettExecutor::enterCombatMode()
{
	enemiesStatus = EnemiesMode::COMBAT;
	Ped player = PLAYER::PLAYER_PED_ID();
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		PED::_0xFE07FF6495D52E2A(*pedItr, 0, 0, 0);
		WEAPON::SET_CURRENT_PED_WEAPON(*pedItr, WEAPON::GET_BEST_PED_WEAPON(*pedItr, 0, 0), true, 0, false, false);

		if (*pedItr == target)
		{
			{
				Object seq;
				AI::OPEN_SEQUENCE_TASK(&seq);
				AI::TASK_COMBAT_PED(target, player, 0, 16);
				AI::CLOSE_SEQUENCE_TASK(seq);

				AI::CLEAR_PED_TASKS(target, 1, 1);
				AI::TASK_PERFORM_SEQUENCE(target, seq);
				playAmbientSpeech(target, "ITS_MALE_EXTREME");
			}
		}
		else
		{
			if (ENTITY::IS_ENTITY_DEAD(*pedItr))
			{
				AI::_0xFD45175A6DFD7CE9(target, player, 3, 0, -999.0f, -1, 0); // FLEE
			}
			Object seq;
			AI::OPEN_SEQUENCE_TASK(&seq);
			AI::_0xFD45175A6DFD7CE9(0, player, 3, 0, -999.0f, -1, 0); // FLEE
			AI::CLOSE_SEQUENCE_TASK(seq);

			AI::CLEAR_PED_TASKS(*pedItr, 1, 1);
			AI::TASK_PERFORM_SEQUENCE(*pedItr, seq);
		}
	}
	if (stopwatch.getElapsedSecondsRealTime() >= 4)
	{
		fail();
	}
}

void ChesterBurnettExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);

	addEnemy(target);
	addEnemy(toVector3(-1351.776, 2436.312, 308.4017));
	addEnemy(toVector3(-1347.818, 2439.917, 308.449));
	addEnemy(toVector3(-1357.465, 2438.535, 308.4151));

	enterIdleMode();
}

void ChesterBurnettExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
}

void ChesterBurnettExecutor::createEnemyBlips()
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

void ChesterBurnettExecutor::releaseUnnecessaryEntities()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	std::vector<Ped>::iterator it;

	if (getMissionStage() >= BountyMissionStage::ArriveToPoliceStation)
	{
		releaseEntitySafe(&horse);

		for (it = enemies.begin(); it != enemies.end(); ++it)
		{
			if (distanceBetweenEntities(*it, player) > 250)
			{
				releaseEntitySafe(&(*it));
			}
		}
	}
}

void ChesterBurnettExecutor::addEnemy(Vector3 pos)
{
	Ped enemyPed = createPed("G_M_M_UNIMICAHGOONS_01", pos);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(target, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
	addEnemy(enemyPed);
}

void ChesterBurnettExecutor::addEnemy(Ped ped)
{
	enemies.push_back(ped);

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
	AI::CLEAR_PED_TASKS(ped, true, true);
}

void ChesterBurnettExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void ChesterBurnettExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false); // give saddle
	horses.push_back(horse);
}

void ChesterBurnettExecutor::cleanup()
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
}
#include "Main.h";

using namespace std;

const int IDLE_DIST = 35;
const int ALERT_DIST = 25;
const int WARN_DIST = 20;
const int HEARING_RANGE = 35;
const int COMBAT_RANGE = 12;

TurkishRunnerExecutor::TurkishRunnerExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(150);
	setRequiredDistanceToLocateTarget(45);
	setMustBeCloseToLocate(true);
	enemiesStatus = EnemiesMode::IDLE;
	campfirePos = toVector3(-2815.12, -2613.38, 92.7243);
	toleratePlayer = true;
	campfire = NULL;
	horse = NULL;
}

void TurkishRunnerExecutor::update()
{
	BaseMissionExecutor::update();
	releaseUnnecessaryEntities();

	Ped player = PLAYER::PLAYER_PED_ID();
	if (getMissionStage() == BountyMissionStage::CaptureTarget)
	{
		float distanceToTarget = distanceBetweenEntities(target, player);
		displayDebugText(to_string(distanceToTarget).c_str());
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

	if (getMissionStage() == BountyMissionStage::CaptureTarget && enemiesStatus >= EnemiesMode::ALERTED && !ENTITY::IS_ENTITY_DEAD(target))
	{
		if (distanceBetweenEntities(target, player) > 100)
		{
			showSubtitle("The target is getting too far!");
		}
		else if (distanceBetweenEntities(target, player) > 80)
		{
			fail("Bounty failed, target lost");
		}
	}

}

Ped TurkishRunnerExecutor::spawnTarget()
{
	Ped target = createPed("G_M_M_UniBanditos_01", toVector3(-2817.15, -2614.94, 92.8264));
	AUDIO::SET_AMBIENT_VOICE_NAME(target, "1021_G_M_M_UNIBANDITOS_01_HISPANIC_03");
	return target;
}

void TurkishRunnerExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", campfirePos);

	this->horse = createPed("A_C_Horse_Turkoman_Gold", toVector3(-2824.89, -2611.77, 92.867));
	addHorse(horse);
	addHorse("A_C_Horse_KentuckySaddle_Black", toVector3(-2821.52, -2610.63, 92.8223));
	addHorse("A_C_Horse_KentuckySaddle_SilverBay", toVector3(-2823.78, -2617.84, 92.9854));

	addEnemy(target);
	addEnemy(toVector3(-2813.18, -2610.57, 92.5611));
	addEnemy(toVector3(-2817.03, -2610.64, 92.7105));
	addEnemy(toVector3(-2812.38, -2614.95, 92.5829));
	addEnemy(toVector3(-2812.46, -2612.73, 92.5725));

	enterIdleMode();
}

void TurkishRunnerExecutor::onTargetLocated()
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

void TurkishRunnerExecutor::cleanup()
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

void TurkishRunnerExecutor::addEnemy(Vector3 pos)
{
	Ped enemyPed = createPed("G_M_M_UniBanditos_01", pos);
	addEnemy(enemyPed);
}

void TurkishRunnerExecutor::addEnemy(Ped ped)
{
	enemies.push_back(ped);

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
	AI::CLEAR_PED_TASKS(ped, true, true);
}

void TurkishRunnerExecutor::addHorse(const char* model, Vector3 pos)
{
	Ped horse = createPed((char*)model, pos);
	addHorse(horse);
}

void TurkishRunnerExecutor::addHorse(Ped horse)
{
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
	PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false); // give saddle
	horses.push_back(horse);
}

void TurkishRunnerExecutor::releaseUnnecessaryEntities()
{
	Ped player = PLAYER::PLAYER_PED_ID();

	if (getMissionStage() >= BountyMissionStage::ArriveToPoliceStation)
	{
		vector<Ped>::iterator pedItr;

		for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
		{
			if (distanceBetweenEntities(*pedItr, player) > 250 || ENTITY::IS_ENTITY_DEAD(*pedItr))
			{
				releaseEntitySafe(&(*pedItr));
			}
		}
	}
}

void TurkishRunnerExecutor::enterIdleMode()
{
	char* scenarioName;

	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		scenarioName = enemies.size() % 2 == 0 ? "WORLD_HUMAN_SIT_GROUND" : "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK";
		Object seq;
		AI::OPEN_SEQUENCE_TASK(&seq);
		AI::TASK_TURN_PED_TO_FACE_COORD(0, campfirePos.x, campfirePos.y, campfirePos.z, 1000);
		AI::_0x524B54361229154F(0, GAMEPLAY::GET_HASH_KEY(scenarioName), -1, true, true, 0, true); // PLAY SCENARIO
		AI::CLOSE_SEQUENCE_TASK(seq);
		AI::TASK_PERFORM_SEQUENCE(*pedItr, seq);
	}

	enemiesStatus = EnemiesMode::IDLE;
}

void TurkishRunnerExecutor::enterAlertMode()
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

void TurkishRunnerExecutor::enterWarningMode()
{
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		pedEquipBestWeapon(*pedItr);
	}

	playAmbientSpeech(target, "FINAL_WARNING");
	enemiesStatus = EnemiesMode::WARNING;
}

void TurkishRunnerExecutor::enterCombatMode()
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
			Object seq;
			AI::OPEN_SEQUENCE_TASK(&seq);
			AI::_0x92DB0739813C5186(0, horse, -1, -1, 2.0f, 1, 0, 0); // Mount the horse
			AI::_0xFD45175A6DFD7CE9(0, player, 3, 0, -999.0f, -1, 0); // FLEE
			AI::CLOSE_SEQUENCE_TASK(seq);

			AI::CLEAR_PED_TASKS(target, 1, 1);
			AI::TASK_PERFORM_SEQUENCE(target, seq);
			playAmbientSpeech(target, "ITS_MALE_EXTREME");
		}
		else
		{
			Object seq;
			AI::OPEN_SEQUENCE_TASK(&seq);
			AI::TASK_COMBAT_PED(0, player, 0, 16);
			AI::CLOSE_SEQUENCE_TASK(seq);

			AI::CLEAR_PED_TASKS(*pedItr, 1, 1);
			AI::TASK_PERFORM_SEQUENCE(*pedItr, seq);
		}
	}
}
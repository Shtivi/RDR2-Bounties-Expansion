#include "Main.h";

using namespace std;

TurkishRunnerExecutor::TurkishRunnerExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(150);
	setRequiredDistanceToLocateTarget(45);
	setMustBeCloseToLocate(true);
	enemiesAlerted = false;
	campfirePos = toVector3(-2815.12, -2613.38, 92.7243);
}

void TurkishRunnerExecutor::update()
{
	BaseMissionExecutor::update();
	releaseUnnecessaryEntities();

	Ped player = PLAYER::PLAYER_PED_ID();
	if (getMissionStage() == BountyMissionStage::CaptureTarget && distanceBetweenEntities(target, player) < 30 && !enemiesAlerted)
	{
		vector<Ped>::iterator pedItr;
		for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
		{
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
			}
			else
			{
				Object seq;
				AI::OPEN_SEQUENCE_TASK(&seq);
				AI::TASK_AIM_GUN_AT_ENTITY(0, player, 3000, 1, 1);
				AI::TASK_COMBAT_PED(0, player, 0, 16);
				AI::CLOSE_SEQUENCE_TASK(seq);

				AI::CLEAR_PED_TASKS(*pedItr, 1, 1);
				AI::TASK_PERFORM_SEQUENCE(*pedItr, seq);
			}
		}

		enemiesAlerted = true;
	}

	if (getMissionStage() == BountyMissionStage::CaptureTarget && enemiesAlerted && !ENTITY::IS_ENTITY_DEAD(target))
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
	char* scenarioName = enemies.size() % 2 == 0 ? "WORLD_HUMAN_SIT_GROUND" : "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK";
	enemies.push_back(ped);

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
	AI::CLEAR_PED_TASKS(ped, true, true);

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_TURN_PED_TO_FACE_COORD(0, campfirePos.x, campfirePos.y, campfirePos.z, 1000);
	AI::_0x524B54361229154F(0, GAMEPLAY::GET_HASH_KEY(scenarioName), -1, true, true, 0, true); // PLAY SCENARIO
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(ped, seq);
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
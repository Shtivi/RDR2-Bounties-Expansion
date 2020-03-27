#include "Main.h";

const float COMBAT_RANGE = 28.0f;
const int LEMOYNE_RAIDERS_MODELS_COUNT = 2;
char* const LEMOYNE_RAIDERS_MODELS[LEMOYNE_RAIDERS_MODELS_COUNT] = {"g_m_o_uniexconfeds_01", "g_m_y_uniexconfeds_01"/*, "g_m_y_uniexconfeds_02"*/};
const Hash GATLING_POLICE_WAGON_VEHICLE = 0xB31F8075;
const float FAIL_DISTANCE = 110.0f;

JacobSeedExecutor::JacobSeedExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(140);
	enemiesAlerted = false;
	finishedAlertingEnemies = false;


}

void JacobSeedExecutor::update()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	vector<Ped>::iterator it;
	float distanceToTarget;

	BaseMissionExecutor::update();
	updateEnemies();
	releaseUnnecessaryEntities();

	if (enemiesAlerted && !finishedAlertingEnemies)
	{
		enemyShootGatling(shooter);
		enemyDriveGatling(target);

		for (it = enemies.begin(); it != enemies.end(); ++it)
		{
			if (*it != shooter && *it != target)
			{
				AI::TASK_COMBAT_PED(*it, player, 0, 16);
			}
		}

		finishedAlertingEnemies = true;
	}

	distanceToTarget = distanceBetweenEntities(player, target);
	if (enemiesAlerted && !ENTITY::IS_ENTITY_DEAD(target))
	{
		if (distanceToTarget > FAIL_DISTANCE)
		{
			fail("Bounty failed, target lost");
		}
		else if (distanceToTarget > FAIL_DISTANCE * 0.8)
		{
			showSubtitle("The target is getting away!");
		}
	}
}

Ped JacobSeedExecutor::spawnTarget()
{
	Ped target = createPed("g_m_o_uniexconfeds_01", toVector3(1552.53, -369.602, 80.6158), 163.664);
	addEnemy(target);
	return target;
}

void JacobSeedExecutor::prepareSet()
{
	campfire = createProp("P_CAMPFIRE02X", toVector3(1551.14, -372.55, 80.5242));
	gatlingWagon = createVehicle(GATLING_POLICE_WAGON_VEHICLE, toVector3(1550.35, -363.854, 80.3371), 63.1261);

	shooter = addEnemy(toVector3(1546.45, -369.089, 79.9711), 157.155);
	Ped scouter = addEnemy(toVector3(1560.44, -365.805, 80.0124), 275.14);
	Ped campEnemy1 = addEnemy(toVector3(1550.92, -375.835, 80.4239), 6.18465);
	Ped campEnemy2 = addEnemy(toVector3(1547.77, -373.901, 80.2731), 306.579);

	enemyScout(shooter, 157.155);
	enemyScout(scouter, 275.14);
	enemySitCamp(target);
	enemySitCamp(campEnemy1);
	enemySitCamp(campEnemy2);
}

void JacobSeedExecutor::onTargetLocated()
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

void JacobSeedExecutor::updateEnemies()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	std::vector<Ped>::iterator it;

	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(*it, player, 1) &&
			distanceBetweenEntities(*it, player) < COMBAT_RANGE)
		{
			enemiesAlerted = true;
		}
	}
}

void JacobSeedExecutor::releaseUnnecessaryEntities()
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

void JacobSeedExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();

	releaseEntitySafe(&campfire);
	releaseEntitySafe(&gatlingWagon);

	vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		releaseEntitySafe(&(*it));
	}
}

Ped JacobSeedExecutor::addEnemy(Vector3 pos, float heading)
{
	char* model = LEMOYNE_RAIDERS_MODELS[enemies.size() % LEMOYNE_RAIDERS_MODELS_COUNT];
	Ped enemy = createPed(model, pos);
	addEnemy(enemy);
	return enemy;
}

void JacobSeedExecutor::addEnemy(Ped enemy)
{
	enemies.push_back(enemy);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(enemy, true);
}

void JacobSeedExecutor::enemySitCamp(Ped ped)
{
	AI::_0x524B54361229154F(ped, GAMEPLAY::GET_HASH_KEY("WORLD_HUMAN_SIT_GROUND"), -1, true, true, 0, true); // PLAY SCENARIO
}

void JacobSeedExecutor::enemyScout(Ped enemy, float heading)
{
	Vector3 position = ENTITY::GET_ENTITY_COORDS(enemy, 1, 0);
	AI::TASK_STAND_GUARD(enemy, position.x, position.y, position.z, heading, "WORLD_HUMAN_GUARD_SCOUT");
}

void JacobSeedExecutor::enemyShootGatling(Ped enemy)
{
	Ped player = PLAYER::PLAYER_PED_ID();

	if (ENTITY::IS_ENTITY_DEAD(enemy) || ENTITY::IS_ENTITY_DEAD(gatlingWagon))
	{
		return;
	}

	int seat = -2;
	VEHICLE::_0xFF5791B7639C2A46(gatlingWagon, (Any*)&seat);
	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_ENTER_VEHICLE(0, gatlingWagon, 20000, seat, 2, 1, 0);
	AI::TASK_VEHICLE_SHOOT_AT_PED(0, player, 20);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(enemy, seq);
}

void JacobSeedExecutor::enemyDriveGatling(Ped enemy)
{
	Ped player = PLAYER::PLAYER_PED_ID();

	if (ENTITY::IS_ENTITY_DEAD(enemy) || ENTITY::IS_ENTITY_DEAD(gatlingWagon))
	{
		return;
	}

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_ENTER_VEHICLE(0, gatlingWagon, 20000, -1, 2, 1, 0);
	AI::_0xFD45175A6DFD7CE9(0, player, 3, 0, -999.0f, -1, 0); // FLEE
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(enemy, seq);
}
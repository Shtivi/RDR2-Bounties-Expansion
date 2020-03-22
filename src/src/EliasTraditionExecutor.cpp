#include "Main.h";

EliasTraditionExecutor::EliasTraditionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
}

void EliasTraditionExecutor::update() 
{
	BaseMissionExecutor::update();
	updateEnemies();
	releaseUnnecessaryEntities();
}

Ped EliasTraditionExecutor::spawnTarget()
{
	Vector3 targetPos = toVector3(-2033.78, -1914.03, 109.976);
	Ped target = createPed(SKINNER_BROTHER_MODEL, targetPos);
	addGuard(target);
	return target;
}

void EliasTraditionExecutor::prepareSet()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);

	horse = createPed("A_C_Horse_Turkoman_DarkBay", toVector3(-2038.82, -1912.17, 110.337));
	addGuard(toVector3(-2029.45, -1907.8, 110.041));
	addGuard(toVector3(-2023.57, -1905.58, 110.068));

	// Killed peds
	int victimNo;
	for (victimNo = 1; victimNo <= 2; victimNo++)
	{
		char* model = victimNo % 2 == 0 ? F_LOWER_TOWN_FOLK : M_LOWER_TOWN_FOLK;
		Ped victim = createPed(model, toVector3(-2033.07, -1908.37, 110.075));
		ENTITY::SET_ENTITY_HEALTH(victim, 0, 0);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&victim);
	}
}

void EliasTraditionExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	createEnemyBlips();
	//playVictimsExecution();
}

void EliasTraditionExecutor::createEnemyBlips()
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

void EliasTraditionExecutor::updateEnemies()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	std::vector<Ped>::iterator it;

	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(*it, player, 1) &&
			distanceBetweenEntities(*it, player) < 28)
		{
			AI::TASK_COMBAT_PED(*it, player, 0, 16);
		}
	}
}

void EliasTraditionExecutor::addGuard(Vector3 position)
{
	Ped guard = createPed(SKINNER_BROTHER_MODEL, position);
	addGuard(guard);
}

void EliasTraditionExecutor::addGuard(Ped guard)
{
	Vector3 position = ENTITY::GET_ENTITY_COORDS(guard, 1, 0);
	AI::CLEAR_PED_TASKS(guard, true, true);
	AI::TASK_STAND_GUARD(guard, position.x, position.y, position.z, 0, "WORLD_HUMAN_GUARD_SCOUT");
	PED::SET_PED_KEEP_TASK(guard, true);
	enemies.push_back(guard);
}

void EliasTraditionExecutor::releaseUnnecessaryEntities()
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

void EliasTraditionExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();

	releaseEntitySafe(&horse);

	std::vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		releaseEntitySafe(&(*it));
	}
}
#include "Main.h";

const Vector3 VICTIMS_POS = toVector3(-2033.07, -1908.37, 110.075);
const int COMBAT_RANGE = 22;
const int EXECUTION_RANGE = 34;

EliasTraditionExecutor::EliasTraditionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(130);

	enemiesAlerted = false;
}

void EliasTraditionExecutor::update()
{
	BaseMissionExecutor::update();

	Ped player = PLAYER::PLAYER_PED_ID();
	updateEnemies();

	if (distanceBetweenEntities(target, player) < EXECUTION_RANGE && !executedVictim)
	{
		playVictimExecution();
		executedVictim = true;
	}
		
	if (enemiesAlerted)
	{
		vector<Ped>::iterator it;

		for (it = enemies.begin(); it != enemies.end(); ++it)
		{
			AI::TASK_COMBAT_PED(*it, player, 0, 16);
		}
	}

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
	vector<Ped>::iterator enemiesItr;
	int victimNo;

	horse = createPed("A_C_Horse_Turkoman_DarkBay", toVector3(-2038.82, -1912.17, 110.337));
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);

	killer = addGuard(toVector3(-2029.45, -1907.8, 110.041));
	addGuard(toVector3(-2023.57, -1905.58, 110.068));
	addGuard(toVector3(-2039.7, -1906.49, 109.158));

	victim = createPed(F_LOWER_TOWN_FOLK, VICTIMS_POS);
	AI::CLEAR_PED_TASKS(victim, 1, 1);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(victim, true);
	AI::TASK_HANDS_UP(victim, 99999, killer, -1, 0);
	PED::SET_PED_KEEP_TASK(victim, true);
}

void EliasTraditionExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	createEnemyBlips();
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
			distanceBetweenEntities(*it, player) < COMBAT_RANGE)
		{
			enemiesAlerted = true;
		}
	}
}

Ped EliasTraditionExecutor::addGuard(Vector3 position)
{
	Ped guard = createPed(SKINNER_BROTHER_MODEL, position);
	addGuard(guard);
	return guard;
}

void EliasTraditionExecutor::addGuard(Ped guard)
{
	Vector3 position = ENTITY::GET_ENTITY_COORDS(guard, 1, 0);
	enemies.push_back(guard);

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_TURN_PED_TO_FACE_COORD(0, VICTIMS_POS.x, VICTIMS_POS.y, VICTIMS_POS.z, 2000);
	AI::TASK_STAND_GUARD(0, position.x, position.y, position.z, 0, "WORLD_HUMAN_GUARD_SCOUT");
	AI::CLOSE_SEQUENCE_TASK(seq);

	AI::CLEAR_PED_TASKS(guard, true, true);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(guard, true);
	AI::TASK_PERFORM_SEQUENCE(guard, seq);
	PED::SET_PED_KEEP_TASK(guard, true);
}

void EliasTraditionExecutor::playVictimExecution()
{
	Object seq;
	Vector3 killerPos = ENTITY::GET_ENTITY_COORDS(killer, 1, 0);

	if (!WEAPON::HAS_PED_GOT_WEAPON(killer, 0x28950C71, 0, 0))
	{
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(killer, 0x28950C71, 0, false, false);
	}

	WEAPON::SET_CURRENT_PED_WEAPON(killer, 0x28950C71, true, 0, false, false);

	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_GO_TO_ENTITY(0, victim, 10000, 0.4f, 1, 0, 0);
	AI::TASK_COMBAT_PED(0, victim, 0, 16);
	//AI::_0x502EC17B1BED4BFA(0, victim); // Pickup victim
	//AI::_0x6D3D87C57B3D52C7(0, victim, horse, 0); // Place on mount
	//AI::TASK_GO_STRAIGHT_TO_COORD(0, killerPos.x, killerPos.y, killerPos.z, 1, -1,)
	AI::TASK_STAND_GUARD(0, -2036.25, -1919.92, 108.586, 0, "WORLD_HUMAN_GUARD_SCOUT");
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::CLEAR_PED_TASKS(killer, 1, 1);
	AI::TASK_PERFORM_SEQUENCE(killer, seq);
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
	releaseEntitySafe(&victim);
	vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		releaseEntitySafe(&(*it));
	}
}
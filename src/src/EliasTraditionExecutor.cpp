#include "Main.h";

EliasTraditionExecutor::EliasTraditionExecutor(BountyMissionData missionData)
	: BaseMissionExecutor(missionData)
{
}

void EliasTraditionExecutor::update() 
{
	BaseMissionExecutor::update();
	updateBlips();
	releaseUnnecessaryEntities();
}

Ped EliasTraditionExecutor::spawnTarget()
{
	//Vector3 targetPos = toVector3(-2031.61, -1921.25, 109.29);
	Vector3 targetPos = toVector3(-2033.78, -1914.03, 109.976);
	Ped target = createPed(SKINNER_BROTHER_MODEL, targetPos);
	
	AI::CLEAR_PED_TASKS(target, true, true);
	PED::SET_PED_KEEP_TASK(target, true);
	AI::TASK_STAND_GUARD(target, targetPos.x, targetPos.y, targetPos.z, 0, "WORLD_HUMAN_GUARD_SCOUT");
	return target;
}

void EliasTraditionExecutor::prepareSet()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);

	Vector3 vehPos = toVector3(-2038.82, -1912.17, 110.337);
	//wagon = createVehicle(0x9780442F, vehPos);
	horse = createPed("A_C_Horse_Turkoman_DarkBay", vehPos);

	killer = createPed(SKINNER_BROTHER_MODEL, toVector3(-2029.45, -1907.8, 110.041));
	WEAPON::REMOVE_ALL_PED_WEAPONS(killer, true, 0);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(killer, 0x28950C71, 0, true, 0);
	enemies.push_back(killer);

	addGuard(toVector3(-2023.57, -1905.58, 110.068));

	victim = createPed(M_LOWER_TOWN_FOLK, toVector3(-2033.07, -1908.37, 110.075));
	AI::CLEAR_PED_TASKS(victim, true, true);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(victim, true);
	AI::TASK_COWER(victim, 999999999, 0, 0);

	PED::REGISTER_TARGET(killer, victim, true);
}

void EliasTraditionExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	createEnemyBlips();
	playVictimsExecution();
}

void EliasTraditionExecutor::createEnemyBlips()
{
	std::vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		createBlip(*it, BLIP_STYLE_ENEMY);
	}
}

void EliasTraditionExecutor::updateBlips()
{
	std::vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		Blip enemyBlip = RADAR::GET_BLIP_FROM_ENTITY(*it);
		if (ENTITY::IS_ENTITY_DEAD(*it) && RADAR::DOES_BLIP_EXIST(enemyBlip))
		{
			RADAR::REMOVE_BLIP(&enemyBlip);
		}
	}
}

void EliasTraditionExecutor::playVictimsExecution()
{
	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_TURN_PED_TO_FACE_ENTITY(0, victim, 1000, 0, 0, 0);
	AI::TASK_COMBAT_PED(0, victim, 0, 16);
	AI::_0x502EC17B1BED4BFA(0, victim);
	AI::_0x6D3D87C57B3D52C7(0, victim, horse, 10);
	AI::_0x92DB0739813C5186(0, horse, 0, 0, 0, 1, 0, 0);
	AI::CLOSE_SEQUENCE_TASK(seq);

	AI::CLEAR_PED_TASKS(killer, true, true);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(killer, true);
	AI::TASK_PERFORM_SEQUENCE(killer, seq);
	PED::SET_PED_KEEP_TASK(killer, true);
}

void EliasTraditionExecutor::addGuard(Vector3 position)
{
	Ped guard = createPed(SKINNER_BROTHER_MODEL, position);
	AI::CLEAR_PED_TASKS(guard, true, true);
	PED::SET_PED_KEEP_TASK(guard, true);
	AI::TASK_STAND_GUARD(guard, position.x, position.y, position.z, 0, "WORLD_HUMAN_GUARD_SCOUT");
	enemies.push_back(guard);
}

void EliasTraditionExecutor::releaseUnnecessaryEntities()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	std::vector<Ped>::iterator it;

	if (getMissionStage() >= BountyMissionStage::ArriveToPoliceStation)
	{
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&horse);

		for (it = enemies.begin(); it != enemies.end(); ++it)
		{
			if (distanceBetweenEntities(*it, player) > 120 || 
				ENTITY::IS_ENTITY_DEAD(*it))
			{
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&(*it));
			}
		}
	}
}

void EliasTraditionExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();

	ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&horse);

	std::vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (ENTITY::DOES_ENTITY_EXIST(*it))
		{
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&(*it));
		}
	}
}
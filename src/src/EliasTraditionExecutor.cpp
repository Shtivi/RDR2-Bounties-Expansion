#include "Main.h";
#include "ExecuteVictimInteraction.h";

const Vector3 VICTIMS_POS = toVector3(-2033.07, -1908.37, 110.075);
const int COMBAT_RANGE = 18;
const int EXECUTION_RANGE = 35;
const int HEARING_RANGE = 40;

EliasTraditionExecutor::EliasTraditionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(130);
	setMustBeCloseToLocate(true);
	executionCleanedUp = false;
	enemiesAlerted = false;
}

void EliasTraditionExecutor::update()
{
	BaseMissionExecutor::update();

	Ped player = PLAYER::PLAYER_PED_ID();
	updateEnemies();

	if (!executedVictim && 
		(distanceBetweenEntities(target, player) < EXECUTION_RANGE) && 
		ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(player, victim, 0))
	{
		executedVictim = true;
		playVictimExecution();
	}
	
	if (executedVictim && victim && ENTITY::DOES_ENTITY_EXIST(victim) && ENTITY::IS_ENTITY_DEAD(victim) && !executionCleanedUp)
	{
		executionCleanedUp = true;
		cleanUpExecution();
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

	campfire = createProp("P_CAMPFIRE02X", toVector3(-2031.62, -1921.61, 108.276));
	horse = createPed("A_C_Horse_KentuckySaddle_Black", toVector3(-2038.82, -1912.17, 110.337));
	giveSaddleToHorse(horse, HorseSaddleHashes::CHARRO_01_STOCK_NEW_SADDLE_000);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);

	killer = addGuard(toVector3(-2029.45, -1907.8, 110.041));
	addGuard(toVector3(-2023.57, -1905.58, 110.068));
	addGuard(toVector3(-2039.7, -1906.49, 109.158));

	victim = createPed(F_LOWER_TOWN_FOLK, VICTIMS_POS);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(victim, true);
	AI::CLEAR_PED_TASKS(victim, 1, 1);
	AI::TASK_HANDS_UP(victim, 99999, killer, -1, 0);
	
	AI::TASK_TURN_PED_TO_FACE_ENTITY(killer, victim, -1, 0, 0, 0);
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
	bool justAlerted = false;

	if (!enemiesAlerted)
	{
		for (it = enemies.begin(); it != enemies.end(); ++it)
		{
			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(*it, player, 1) &&
				distanceBetweenEntities(*it, player) < COMBAT_RANGE)
			{
				enemiesAlerted = true;
				justAlerted = true;
			}
		}

		if (PED::IS_PED_SHOOTING(player) && distanceBetweenEntities(target, player) < HEARING_RANGE)
		{
			enemiesAlerted = true;
			justAlerted = true;
		}
	}

	if (enemiesAlerted && justAlerted)
	{
		playAmbientSpeech(target, "ITS_THEM_EXTREME");
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
	AI::TASK_STAND_GUARD(0, position.x, position.y, position.z, 0, "WORLD_HUMAN_GUARD_SCOUT");
	AI::CLOSE_SEQUENCE_TASK(seq);

	AI::CLEAR_PED_TASKS(guard, true, true);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(guard, true);
	AI::TASK_PERFORM_SEQUENCE(guard, seq);
	AI::CLEAR_SEQUENCE_TASK(&seq);
}

void EliasTraditionExecutor::playVictimExecution()
{
	Vector3 killerPos = ENTITY::GET_ENTITY_COORDS(killer, 1, 0);
	giveWeaponToPed(killer, WeaponHash::MeleeMachete, 0, true);
	
	std::vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (*it != killer)
		{
			AI::CLEAR_PED_TASKS(*it, 1, 1);
			AI::TASK_TURN_PED_TO_FACE_ENTITY(*it, victim, -1, 0, 0, 0);
		}
	}

	Conversation conv;
	conv.addLine(target, "CALLOUT_JUST_KILL_EM_NEUTRAL");
	conv.addLine(new ExecuteVictimInteraction(victim, killer));
	conv.addLine(victim, "PLEAD");
	conv.addLine(victim, "PANIC_HELP");
	conv.play();
}

void EliasTraditionExecutor::cleanUpExecution()
{
	std::vector<Ped>::iterator it;
	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_GO_TO_ENTITY(0, campfire, 20000, 1.5f, 1, 0, 0);
	AI::_0x524B54361229154F(0, GAMEPLAY::GET_HASH_KEY("WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK"), -1, true, true, 0, true); // PLAY SCENARIO
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::CLEAR_PED_TASKS(killer, 1, 1);
	AI::TASK_PERFORM_SEQUENCE(killer, seq);
	AI::CLEAR_SEQUENCE_TASK(&seq);

	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (*it != killer)
		{
			Vector3 position = ENTITY::GET_ENTITY_COORDS(*it, 1, 1);
			AI::CLEAR_PED_TASKS(*it, 1, 1);
			AI::TASK_STAND_GUARD(*it, position.x, position.y, position.z, 0, "WORLD_HUMAN_GUARD_SCOUT");
		}
	}
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
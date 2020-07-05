#include "Main.h";

GenericGuardingBehavior::GenericGuardingBehavior(Ped ped, Vector3 defensePosition, float radius, bool shouldTolerate, IdlingModifier idlingModifier)
	: PedBehavior(ped)
{
	this->defensePosition = defensePosition;
	this->radius = radius;
	setShouldTolerate(shouldTolerate);
	setMode(TensionMode::Idle);
	setIdlingModifier(idlingModifier);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
}

GenericGuardingBehavior::GenericGuardingBehavior(Ped ped, Vector3 defensePosition, float radius, IdlingModifier idlingModifier, RoutineParams routineParams, set<Ped>* bodiesFound, bool shouldTolerate)
	: GenericGuardingBehavior(ped, defensePosition, radius, shouldTolerate, idlingModifier)
{
	this->routineParams = routineParams;
	
	if (bodiesFound)
	{
		this->bodiesFound = bodiesFound;;
	}
	else
	{
		this->bodiesFound = new set<Ped>();
	}
}


void GenericGuardingBehavior::start(bool withBlip)
{
	PedBehavior::start();
	setMode(TensionMode::Idle);
	enterIdleMode();

	if (withBlip)
	{
		addEnemyBlip();
	}
}

void GenericGuardingBehavior::stop()
{
	PedBehavior::stop();
	removeBlip();
}

void GenericGuardingBehavior::update()
{
	PedBehavior::update();
	if (!isActive())
	{
		return;
	}

	Ped player = PLAYER::PLAYER_PED_ID();
	float distanceFromGuard = distanceBetweenEntities(ped(), player);
	float distanceFromCenter = distanceBetween(ENTITY::GET_ENTITY_COORDS(player, 1, 0), getDefensePosition());

	switch (mode)
	{
	case TensionMode::Idle:
		if (distanceFromCenter <= GUARD_SUSPECT_RANGE + radius && isPlayerWithinLos())
		{
			if (shouldTolerate())
			{
				enterSuspectionMode();
			}
		}
		else
		{
			detectHighProfileEventAround();
		}
		break;

	case TensionMode::Suspect:
		if (stopwatch.getElapsedSecondsRealTime() >= 5)
		{
			if (shouldTolerate())
			{
				enterWarningMode();
			}
			else
			{
				enterCombatMode();
			}
		}
		else if (distanceFromCenter >= GUARD_IDLE_RANGE + radius)
		{
			stopwatch.stop();
			enterIdleMode();
		}
		break;

	case TensionMode::Warn:
		if (stopwatch.getElapsedSecondsRealTime() >= 4)
		{
			if (distanceFromCenter >= GUARD_SUSPECT_RANGE + radius)
			{
				setShouldTolerate(false);
				stopwatch.stop();
				enterSuspectionMode();
			}
			else
			{
				enterCombatMode();
			}
		}
		break;

	case TensionMode::Alerted:
		if (isPlayerWithinLos())
		{
			enterCombatMode();
		}
		else
		{
			detectHighProfileEventAround();
		}
		break;

	case TensionMode::Search:
		if (isPlayerWithinLos())
		{
			enterCombatMode();
		}
		else if (stopwatch.getElapsedSecondsRealTime() >= GUARD_SEARCH_DURATION_SECS)
		{
			showSubtitle("stopped searching");
			stopwatch.stop();
			enterAlertedMode();
		}
		break;

	case TensionMode::Combat:
		break;
	}

	if (getMode() < TensionMode::Combat)
	{
		Vector3 lastImpactCoords;

		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(player, &lastImpactCoords) &&
			distanceBetween(ENTITY::GET_ENTITY_COORDS(ped(), 1, 0), lastImpactCoords) <= GUARD_SUSPECT_RANGE &&
			PED::IS_PED_SHOOTING(player))
		{
			if (distanceFromGuard <= GUARD_SEEING_RANGE)
			{
				enterCombatMode();
			}
			else
			{
				enterSearchMode(ENTITY::GET_ENTITY_COORDS(ped(), 1, 0));
			}
		}
		else if ((distanceFromGuard <= GUARD_HEARING_RANGE && PED::IS_PED_SHOOTING(player)) || 
				 ((distanceFromCenter <= GUARD_COMBAT_RANGE + radius || PLAYER::IS_PLAYER_FREE_AIMING(player)) && isPlayerWithinLos()))
		{
			enterCombatMode();
		}
	}
}

void GenericGuardingBehavior::routine()
{
	AI::CLEAR_PED_TASKS(ped(), 1, 1);
	if (getIdlingModifier() == IdlingModifier::Scout)
	{
		scout();
	}
	else
	{
		patrol();
	}
}

void GenericGuardingBehavior::scout()
{
	Vector3 currentPosition = ENTITY::GET_ENTITY_COORDS(ped(), 1, 0);
	float currentHeading = ENTITY::GET_ENTITY_HEADING(ped());

	if (distanceBetween(routineParams.scoutPosition, toVector3(0,0,0)) != 0)
	{
		scout(routineParams.scoutPosition, routineParams.scoutHeading);
	}
	else
	{
		scout(currentPosition, currentHeading);
	}
}

void GenericGuardingBehavior::scout(Vector3 scoutPosition, float heading)
{
	this->routineParams.scoutPosition = scoutPosition;
	this->routineParams.scoutHeading = heading;
	setIdlingModifier(IdlingModifier::Scout);

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_GO_TO_COORD_ANY_MEANS(0, scoutPosition.x, scoutPosition.y, scoutPosition.z, 1.0f, 0, 0, 1, 0);
	AI::TASK_STAND_GUARD(0, scoutPosition.x, scoutPosition.y, scoutPosition.z, heading, generateScoutingScenario());
	//AI::_0x524B54361229154F(0, GAMEPLAY::GET_HASH_KEY(generateScoutingScenario()), -1, true, true, 0, true); // PLAY SCENARIO
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(ped(), seq);
}

void GenericGuardingBehavior::patrol()
{
	if (routineParams.patrolRoute.size() == 0)
	{
		vector<Vector3> nodes;
		nodes.push_back(getRandomPedPositionInRange(defensePosition, radius));
		nodes.push_back(getRandomPedPositionInRange(defensePosition, radius));
		nodes.push_back(getRandomPedPositionInRange(defensePosition, radius));
		patrol(nodes);
	}
	else
	{
		patrol(routineParams.patrolRoute);
	}
}

void GenericGuardingBehavior::patrol(vector<Vector3> nodes)
{
	this->routineParams.patrolRoute = nodes;

	int i = 0;
	vector<Vector3>::iterator itr = nodes.begin();
	AI::OPEN_PATROL_ROUTE("miss_brob1_patrolLM02");
	while (itr != nodes.end())
	{
		AI::ADD_PATROL_ROUTE_NODE(i, generateScoutingScenario(), (*itr).x, (*itr).y, (*itr).z, 0, 0, 0, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(4000, 8000), 0);
		
		if (i + 1 < nodes.size())
		{
			AI::ADD_PATROL_ROUTE_LINK(i, i+1);
		}
		else
		{
			AI::ADD_PATROL_ROUTE_LINK(i, 0);
		}
		
		i++;
		itr++;
	}
	AI::CLOSE_PATROL_ROUTE();
	AI::CREATE_PATROL_ROUTE();
	AI::TASK_PATROL(ped(), "miss_brob1_patrolLM02", 1, 1, 1);
	setIdlingModifier(IdlingModifier::Patrol);
}

void GenericGuardingBehavior::alert()
{
	if (getMode() != TensionMode::Alerted)
	{
		setMode(TensionMode::Alerted);
		enterAlertedMode();
	}
}

void GenericGuardingBehavior::search()
{
	search(ENTITY::GET_ENTITY_COORDS(ped(), 1, 0));
}

void GenericGuardingBehavior::search(Vector3 aroundWhere, float radius)
{
	if (getMode() != TensionMode::Search)
	{
		setMode(TensionMode::Search);
		enterSearchMode(aroundWhere, radius);
	}
}

void GenericGuardingBehavior::combat()
{
	if (getMode() != TensionMode::Combat)
	{
		setMode(TensionMode::Combat);
		enterCombatMode();
	}
}

void GenericGuardingBehavior::addEnemyBlip()
{
	if (!RADAR::DOES_BLIP_EXIST(RADAR::GET_BLIP_FROM_ENTITY(ped())))
	{
		createBlip(ped(), BLIP_STYLE_ENEMY);
	}
}

void GenericGuardingBehavior::removeBlip()
{
	Blip pedBlip = RADAR::GET_BLIP_FROM_ENTITY(ped());
	deleteBlipSafe(&pedBlip);
}

TensionMode GenericGuardingBehavior::getMode()
{
	return this->mode;
}

Vector3 GenericGuardingBehavior::getDefensePosition()
{
	return this->defensePosition;
}

float GenericGuardingBehavior::getRadius()
{
	return this->radius;
}

bool GenericGuardingBehavior::shouldTolerate()
{
	return _shouldTolerate;
}

void GenericGuardingBehavior::setShouldTolerate(bool flag)
{
	_shouldTolerate = flag;
}

IdlingModifier GenericGuardingBehavior::getIdlingModifier()
{
	return this->idlingModifier;
}

bool GenericGuardingBehavior::isPlayerWithinLos()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	float distanceFromGuard = distanceBetweenEntities(ped(), player);
	float distanceFromCenter = distanceBetween(ENTITY::GET_ENTITY_COORDS(player, 1, 0), getDefensePosition());
	bool hasLos = ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(ped(), PLAYER::PLAYER_PED_ID(), 1);

	return /*(distanceFromCenter <= GUARD_IDLE_RANGE + radius) && */(distanceFromGuard <= GUARD_SEEING_RANGE) && hasLos;
}

char* GenericGuardingBehavior::generateScoutingScenario()
{
	int scenarioIdx = rndInt(0, SCOUTING_SCENARIOS_NUM - 1);
	const char* scenario = SCOUTING_SCENARIO_NAMES[scenarioIdx];
	return (char*)scenario;
}

void GenericGuardingBehavior::detectHighProfileEventAround()
{
	HighProfileEvents event = HighProfileEvents::None;
	Vector3 eventOrigin;

	vector<Ped> nearbyPeds = getNearbyDeadBodies(ped(), 20, GUARD_SEEING_RANGE);
	vector<Ped>::iterator itr = nearbyPeds.begin();
	while (itr != nearbyPeds.end() && event == HighProfileEvents::None)
	{
		if (!shouldIgnoreBody(*itr) && (
			distanceBetweenEntities(ped(), *itr) <= GUARD_COMBAT_RANGE || ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(ped(), *itr, 1)))
		{
			event = HighProfileEvents::Body;
			eventOrigin = ENTITY::GET_ENTITY_COORDS(*itr, 0, 1);
		}

		itr++;
	}

	itr = nearbyPeds.begin();
	while (itr != nearbyPeds.end())
	{
		bodiesFound->insert(*itr);
		itr++;
	}

	switch (event)
	{
	case HighProfileEvents::Body:
		log("found a body");
		log(to_string(bodiesFound->size()));
		playAmbientSpeech(ped(), "FOUND_BODY");
		break;
	case HighProfileEvents::Generic:
		playAmbientSpeech(ped(), "WHAT_IS_THAT");
		break;
	default:
		break;
	}

	if (event != HighProfileEvents::None)
	{
		enterSearchMode(eventOrigin);
	}
}

bool GenericGuardingBehavior::shouldIgnoreBody(Ped body)
{
	return (bodiesFound->find(body) != bodiesFound->end());
}

void GenericGuardingBehavior::enterIdleMode()
{
	setMode(TensionMode::Idle);
	routine();
}

void GenericGuardingBehavior::enterSuspectionMode()
{
	AI::TASK_TURN_PED_TO_FACE_ENTITY(ped(), PLAYER::PLAYER_PED_ID(), -1, 0, 0, 0);
	stopwatch.start();

	if (getMode() == TensionMode::Idle)
	{
		playAmbientSpeech(ped(), "GET_LOST");
	}
	else if (getMode() == TensionMode::Warn)
	{
		playAmbientSpeech(ped(), "WON_DISPUTE");
	}

	setMode(TensionMode::Suspect);

}

void GenericGuardingBehavior::enterAlertedMode()
{
	setMode(TensionMode::Alerted);
	pedEquipBestWeapon(ped());
	routine();
}

void GenericGuardingBehavior::enterWarningMode()
{
	stopwatch.start();
	pedEquipBestWeapon(ped());
	playAmbientSpeech(ped(), "FINAL_WARNING");
	setMode(TensionMode::Warn);
}

void GenericGuardingBehavior::enterSearchMode(Vector3 aroundWhere, float searchRadius)
{
	AI::CLEAR_PED_TASKS(ped(), 1, 1);
	pedEquipBestWeapon(ped());

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	for (int i = 1; i <= 3; i++)
	{
		Vector3 goPos = getRandomPedPositionInRange(aroundWhere, searchRadius);
		Vector3 aimPos = goPos + ENTITY::GET_ENTITY_FORWARD_VECTOR(ped()) * 100;
		AI::TASK_GO_TO_COORD_ANY_MEANS(0, goPos.x, goPos.y, goPos.z, 2.0f, 0, 0, 524419, -1);
		AI::TASK_AIM_GUN_AT_COORD(0, aimPos.x, aimPos.y, aimPos.z, 4000, 0, 0);
	}

	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(ped(), seq);

	setMode(TensionMode::Search);
	stopwatch.start();
}

void GenericGuardingBehavior::enterCombatMode()
{
	setMode(TensionMode::Combat);

	Ped player = PLAYER::PLAYER_PED_ID();
	if (!PED::IS_PED_IN_COMBAT(ped(), player))
	{
		PED::_0xFE07FF6495D52E2A(ped(), 0, 0, 0);
		AI::TASK_COMBAT_PED(ped(), player, 0, 16);
	}
	playAmbientSpeech(ped(), "GET_SUSPECT_MALE");
	addEnemyBlip();
}

void GenericGuardingBehavior::setMode(TensionMode mode)
{
	this->mode = mode;
}

void GenericGuardingBehavior::setIdlingModifier(IdlingModifier idlingModifier)
{
	this->idlingModifier = idlingModifier;
}
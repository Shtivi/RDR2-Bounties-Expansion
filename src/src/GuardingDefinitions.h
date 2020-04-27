#pragma once

enum class TensionMode
{
	Idle = 0,
	Suspect,
	Warn,
	Alerted,
	Search,
	Combat
};

enum class HighProfileEvents
{
	None,
	Body,
	Generic
};

enum class IdlingModifier
{
	Rest,
	Scout,
	Patrol
};

class RoutineParams
{
public:
	Vector3 scoutPosition;
	float scoutHeading;
	vector<Vector3> patrolRoute;
};

#include "GenericGuardingBehavior.h"
#include "GuardsGroup.h";
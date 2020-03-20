#pragma once

enum TargetCondition
{
	Alive,
	DeadOrAlive
};

struct BountyMissionData
{
	const char* missionName;
	MapAreas area;
	int reward;
	TargetCondition requiredTargetCondition;
	Vector3 startPosition;
	bool isTargetMale;
	const char* targetName;
	const char* crime;
	const char* description;

	BountyMissionData()
	{}
};
#pragma once

struct BountyMissionData
{
	int id;
	const char* missionName;
	MapAreas area;
	int reward;
	const char* rewardStr;
	TargetCondition requiredTargetCondition;
	Vector3 startPosition;
	bool isTargetMale;
	const char* targetName;
	const char* crime;
	const char* description;

	BountyMissionData()
	{}
};
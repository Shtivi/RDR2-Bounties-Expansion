#pragma once

class MapArea
{
private:
	set<int> areaMissionIds;

public:
	const char* name;
	Vector3* policeDeptCoords;
	Vector3* bountyPostersCoords;
	Vector3* cellCoords;

	MapArea(const char* name, Vector3 policeDeptCoords, Vector3 bountyPostersCoords, Vector3 cellCoords);

	void linkMission(int missionId);
	int nextMission(int fromId);
	set<int>* getMissionIds();
}; 
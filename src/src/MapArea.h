#pragma once

class MapArea
{
private:
	std::vector<int> areaMissionIds;

public:
	const char* name;
	Vector3* policeDeptCoords;
	Vector3* bountyPostersCoords;
	Vector3* cellCoords;

	MapArea(const char* name, Vector3 policeDeptCoords, Vector3 bountyPostersCoords, Vector3 cellCoords);

	void linkMission(int missionId);
	int nextMission(int fromId);
	vector<int>* getMissionIds();
}; 
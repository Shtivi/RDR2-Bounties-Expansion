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
	Vector3* moneyCoords;
	int cellnumber;
	float bountyPosterHeading;

	MapArea(const char* name, Vector3 policeDeptCoords, Vector3 bountyPostersCoords, Vector3 moneyCoords, Vector3 cellCoords, int cellnumber, float bountyPosterHeading = 0);

	void linkMission(int missionId);
	int nextMission(int fromId);
	set<int>* getMissionIds();
}; 
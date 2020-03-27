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
	float bountyPosterHeading;

	MapArea(const char* name, Vector3 policeDeptCoords, Vector3 bountyPostersCoords, Vector3 cellCoords, float bountyPosterHeading = 0);

	void linkMission(int missionId);
	int nextMission(int fromId);
	set<int>* getMissionIds();
}; 
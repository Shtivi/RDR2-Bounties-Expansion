#include "Main.h"

MapArea::MapArea(const char* name, Vector3 policeDeptCoords, Vector3 bountyPostersCoords, Vector3 moneyCoords, Vector3 cellCoords, int cellnumber, float bountyPosterHeading)
{
	this->name = name;
	this->policeDeptCoords = new Vector3(policeDeptCoords);
	this->bountyPostersCoords = new Vector3(bountyPostersCoords);
	this->moneyCoords = new Vector3(moneyCoords);
	this->cellCoords = new Vector3(cellCoords);
	this->cellnumber = cellnumber;
	this->bountyPosterHeading = bountyPosterHeading;
}

void MapArea::linkMission(int missionId)
{
	areaMissionIds.insert(missionId);
}

int MapArea::nextMission(int fromId)
{
	set<int>::iterator it = areaMissionIds.begin();

	while (it != areaMissionIds.end() && *it != fromId)
	{
		++it;
	}

	if (it == areaMissionIds.end() || ++it == areaMissionIds.end())
	{
		return -1;
	}

	return *it;
}

set<int>* MapArea::getMissionIds()
{
	return &(this->areaMissionIds);
}
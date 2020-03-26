#include "Main.h"

MapArea::MapArea(const char* name, Vector3 policeDeptCoords, Vector3 bountyPostersCoords, Vector3 cellCoords)
{
	this->name = name;
	this->policeDeptCoords = new Vector3(policeDeptCoords);
	this->bountyPostersCoords = new Vector3(bountyPostersCoords);
	this->cellCoords = new Vector3(cellCoords);
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
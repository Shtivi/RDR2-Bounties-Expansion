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
	areaMissionIds.push_back(missionId);
	std::sort(areaMissionIds.begin(), areaMissionIds.end());
}

int MapArea::nextMission(int fromId)
{
	std::vector<int>::iterator it = areaMissionIds.begin();
	
	while (it != areaMissionIds.end() && *it != fromId)
	{
		++it;
	}

	if (it == areaMissionIds.end() || it + 1 == areaMissionIds.end())
	{
		return -1;
	}

	++it;
	return *it;
}

vector<int>* MapArea::getMissionIds()
{
	return &(this->areaMissionIds);
}
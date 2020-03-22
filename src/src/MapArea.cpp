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
}

int MapArea::nextMission(int fromId)
{
	std::vector<int>::iterator it;
	
	for (it = areaMissionIds.begin(); it != areaMissionIds.end(); ++it)
	{
		if (*it != fromId)
		{
			continue;
		}

		if (it + 1 == areaMissionIds.end())
		{
			return -1;
		}

		return *it;
	}

	return -1;
}

//int MapArea::nextMission(ModProgress* progress)
//{
//	std::vector<int>::iterator it;
//
//	for (it = areaMissionIds.begin(); it != areaMissionIds.end(); ++it)
//	{
//		if (progress->getMissionProgress(*it) == BountyMissionStatus::Unavailable)
//		{
//			return *it;
//		}
//	}
//
//	return -1;
//}
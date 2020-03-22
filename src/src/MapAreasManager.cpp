#include "Main.h";


MapAreasManager::MapAreasManager()
{
	cache.insert(std::make_pair(Blackwater, createBlackwater()));
}


MapArea* MapAreasManager::getMapArea(MapAreas area)
{
	if (cache.find(area) == cache.end())
	{
		return NULL;
	}

	return cache.find(area)->second;
}

MapArea* MapAreasManager::createBlackwater()
{
	Vector3 policeDeptCoords;
	policeDeptCoords.x = -756.347;
	policeDeptCoords.y = -1269.24;
	policeDeptCoords.z = 43.0285;

	Vector3 cellCoords = toVector3(-765.036, -1264.13, 44.0245);

	Vector3 posterCoords;
	posterCoords.x = -785.882;
	posterCoords.y = -1344.54;
	posterCoords.z = 43.7609;

	return new MapArea("Blackwater", policeDeptCoords, posterCoords, cellCoords);
}
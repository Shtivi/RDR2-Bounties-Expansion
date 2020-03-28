#include "Main.h";


MapAreasManager::MapAreasManager()
{
	cache[Blackwater] = createBlackwater();
	cache[Rhodes] = createRhodes();
	cache[Valentine] = createValentine();
}


MapArea* MapAreasManager::getMapArea(MapAreas area)
{
	if (cache.find(area) == cache.end())
	{
		return NULL;
	}

	return cache.find(area)->second;
}

vector<MapArea*> MapAreasManager::getMapAreas()
{
	vector<MapArea*> results;
	map<MapAreas, MapArea*>::iterator it;
	for (it = cache.begin(); it != cache.end(); it++)
	{
		results.push_back((*it).second);
	}

	return results;
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

MapArea* MapAreasManager::createRhodes()
{
	Vector3 policeDeptCoords = toVector3(1358.17, -1308.19, 76.7296);
	Vector3 cellCoords = toVector3(1357.97, -1301.96, 76.7606);
	Vector3 posterCoords = toVector3(1234.58, -1293.13, 77.2681);

	return new MapArea("Rhodes", policeDeptCoords, posterCoords, cellCoords, 136);
}

MapArea* MapAreasManager::createValentine()
{
	Vector3 policeDeptCoords = toVector3(-275.256, 801.303, 118.397);
	Vector3 cellCoords = toVector3(-275.918, 810.098, 118.376);
	Vector3 posterCoords = toVector3(-298.459, 785.939, 118.204);

	return new MapArea("Valentine", policeDeptCoords, posterCoords, cellCoords, 191.451248);
}